#include "map.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

static uint8_t			ft_check_extension(char *str, char *ext);
static uint8_t			ft_open_file(char *file, int32_t *fd);
static void				ft_map_set_default(t_map *map);
static t_map_exception	ft_check_requirement(t_map *map, char **tmp_map, int32_t fd, size_t i);
static t_map_exception	ft_check_map(t_map *map, char **tmp_map, int32_t fd, bool empty);
static t_map_exception	ft_format_map(t_map *map, char **tmp_map);
uint8_t					ft_resize_map(t_map *map, char **tmp_map);
uint8_t					ft_check_border(t_map *map, char *tmp_map);

char		*ft_read_line(char **str, int32_t fd, char to_skip);
uint8_t		ft_set_args(t_map *map, const t_dictionary *lexic, char *args);
uint8_t		ft_set_path(t_map *map, const t_dictionary *lexic, char *args);
uint8_t		ft_set_rgb(t_map *map, const t_dictionary *lexic, char *args);
size_t		ft_n_occurence(char *str, char c);
size_t		ft_len_till(char *str, char c);
int32_t		ft_eval_width(char *line, int32_t i);

uint8_t	ft_rule_match(t_dictionary *lexic, char *rule, size_t *index);
uint8_t	ft_is_match(t_dictionary *lexic, t_map *tmp_map, char *line, char *rule);
t_dictionary	*ft_set_lexic(t_dictionary	**lexic);
uint8_t	ft_is_valid_map(t_map *map, char *line);
t_orientation	ft_str_to_enum(char *str, t_orientation *pos);

t_map_exception	ft_parse_map(char *file, t_map *map)
{
	char			*tmp_map;
	t_map_exception	map_exception;
	int32_t			fd;

	if (1 == ft_check_extension(file, (char *)".pub"))
		return (EXTENSION_ERROR);
	if (1 == ft_open_file(file, &fd))
		return (OPEN_ERROR);
	ft_map_set_default(map);
	map_exception = ft_check_requirement(map, &tmp_map, fd, 0);
	if (map_exception >= REQUIREMENT_ERROR && map_exception <= RGB_ERROR)
		return (close(fd), map_exception);
	if (ELEMENT_ERROR == ft_check_map(map, &tmp_map, fd, false)
		|| ELEMENT_ERROR == ft_format_map(map, &tmp_map))
		return (close(fd), ELEMENT_ERROR);
	close(fd);
	return (NO_MAP_EXCEPTION);
}

uint8_t	ft_check_extension(char *str, char *ext)
{
	size_t	i;

	i = ft_strlen(str);
	while (str[i] != '.' && i != 0)
		--i;
	return (ft_strcmp(&str[i], ext) != 0);
}

uint8_t	ft_open_file(char *file, int32_t *fd)
{
	*fd = open(file, O_RDONLY);
	return (-1 == *fd);
}

void	ft_map_set_default(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->s_player.e_orientation = N_ORIENTATION;
}

static t_map_exception	ft_check_requirement(t_map *map, char **tmp_map,
												int32_t fd, size_t i)
{
	static t_dictionary	*lexic;
	size_t				index;
	char				**args;
	char				*line;

	if (0 == i && NULL == ft_set_lexic(&lexic))
		return (REQUIREMENT_ERROR);
	ft_read_line(&line, fd, '\n');
	args = ft_split(line, ' ');
	if (ft_dptrlen(args) != 2
		|| ft_rule_match(lexic, args[0], &index) != 0)
	{
		if (NULL == args || ft_is_match(lexic, map, line, args[0]) != 0)
			return (ft_freef("%p, %p, %P", lexic, line, args),
				REQUIREMENT_ERROR);
		*tmp_map = ft_strdup(line);
		return (ft_freef("%p, %p, %P", lexic, line, args),
			NO_MAP_EXCEPTION);
	}
	if (1 == ft_set_args(map, &lexic[index], args[1]))
		return (ft_freef("%p, %p, %P", lexic, line, args),
			lexic[index].exception); // heap use after free
	ft_freef("%p, %P", line, args);
	return (ft_check_requirement(map, tmp_map, fd, ++i));
}

t_dictionary	*ft_set_lexic(t_dictionary	**lexic)
{
	const t_dictionary	tmp_lexic[N_RULE] = {
	{NORTH_TEXTURE, MANDATORY, WALL, NORTH, PATH_ERROR},
	{SOUTH_TEXTURE, MANDATORY, WALL, SOUTH, PATH_ERROR},
	{WEST_TEXTURE, MANDATORY, WALL, WEST, PATH_ERROR},
	{EAST_TEXTURE, MANDATORY, WALL, EAST, PATH_ERROR},
	{FLOOR_RGB, MANDATORY, FLOOR, 0, RGB_ERROR},
	{CEILING_RGB, MANDATORY, CEILING, 0, RGB_ERROR},
	{FLOOR_TEXTURE, NOT_MANDATORY, FLOOR, 0, PATH_ERROR},
	{CEILING_TEXTURE, NOT_MANDATORY, CEILING, 0, PATH_ERROR}
	};
	size_t				i;

	*lexic = ft_calloc(N_RULE + 1, sizeof(t_dictionary));
	if (NULL == *lexic)
		return (NULL);
	i = 0;
	while (i < N_RULE)
	{
		*(*lexic + i) = tmp_lexic[i];
		++i;
	}
	return (*lexic);
}

char	*ft_read_line(char **str, int32_t fd, char to_skip)
{
	*str = ft_get_next_line(fd);
	if (*str != NULL && to_skip == **str)
	{
		free(*str);
		ft_read_line(str, fd, to_skip);
	}
	return (*str);
}

uint8_t	ft_rule_match(t_dictionary *lexic, char *rule, size_t *index)
{
	size_t	i;

	i = 0;
	while (i < N_RULE)
	{
		if (lexic[i].rule_type != MATCH && 0 == ft_strcmp(lexic[i].rule, rule))
		{
			printf("lexic : %s\n rule : %s\n", lexic[i].rule, rule);
			lexic[i].rule_type = MATCH;
			*index = i;
			return (0);
		}
		++i;
	}
	return (1);
}

uint8_t	ft_is_match(t_dictionary *lexic, t_map *map, char *line, char *rule)
{
	size_t	i;

	i = 0;
	while (i < N_RULE)
	{
		if (lexic[i].rule_type == MANDATORY
			|| 0 == ft_strcmp(lexic[i].rule, rule))
			return (1);
		++i;
	}
	return (ft_is_valid_map(map, line));
}

uint8_t	ft_set_args(t_map *map, const t_dictionary *lexic, char *args)
{
	if (PATH_ERROR == lexic->exception)
		return (ft_set_path(map, lexic, args));
	return (ft_set_rgb(map, lexic, args));
}

uint8_t	ft_set_path(t_map *map, const t_dictionary *lexic, char *args)
{
	const size_t	len = ft_strlen(args);
	int32_t			fd;

	if ('\n' == args[len - 1])
		args[len - 1] = '\0';
	if (len >= PATH_MAX || 1 == ft_open_file(args, &fd))
		return (1);
	close(fd);
	ft_strlcpy(map->texture[lexic->element].path[lexic->orientation],
		args,
		len);
	return (0);
}

uint8_t	ft_set_rgb(t_map *map, const t_dictionary *lexic, char *args)
{
	char	**rgb;
	size_t	len;
	int32_t	rgb_val[3];
	bool	is_overflow;

	if (ft_n_occurence(args, ',') != 2)
		return (1);
	rgb = ft_split(args, ',');
	len = ft_dptrlen(rgb);
	if (len != 3)
		return (ft_freef("%P", rgb), 1);
	rgb[len - 1][ft_strlen(rgb[len - 1]) - 1] = '\0';
	while (len-- > 0)
	{
		is_overflow = false;
		rgb_val[len] = ft_strtoi(rgb[len], &is_overflow);
		if (is_overflow == true || rgb_val[len] < 0 || rgb_val[len] > 255)
			return (ft_freef("%P", rgb), 1);
	}
	map->texture[lexic->element].rgb[lexic->orientation]
		= ((rgb_val[0] & 0x0ff) << 16)
		| ((rgb_val[1] & 0x0ff) << 8)
		| (rgb_val[2] & 0x0ff);
	return (ft_freef("%P", rgb), 0);
}

size_t	ft_n_occurence(char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			++j;
		++i;
	}
	return (j);
}

static t_map_exception	ft_check_map(t_map *map, char **tmp_map, int32_t fd, bool empty)
{
	char	*line;
	void	*ptr_cpy;

	if (NULL == *tmp_map)
		return (ELEMENT_ERROR);
	if (NULL == ft_read_line(&line, fd, '\0'))
		return (NO_MAP_EXCEPTION);
	if ('\n' == *line)
		return (free(line), ft_check_map(map, tmp_map, fd, true));
	if (true == empty || ft_is_valid_map(map, line))
		return (ft_freef("%p, %p", *tmp_map, line), ELEMENT_ERROR);
	ptr_cpy = *tmp_map;
	*tmp_map = ft_join(2, *tmp_map, line);
	ft_freef("%p, %p", ptr_cpy, line);
	return (ft_check_map(map, tmp_map, fd, empty));
}

uint8_t	ft_is_valid_map(t_map *map, char *line)
{
	int32_t			i;
	t_orientation	pos;

	i = -1;
	while (line[++i] != '\0')
	{
		if (' ' == line[i])
			line[i] = '1';
		if (N_ORIENTATION == map->s_player.e_orientation
			&& ft_str_to_enum(&line[i], &pos) != N_ORIENTATION)
		{
			map->s_player.s_pos.x = i + 0.5;
			map->s_player.s_pos.y = map->height + 0.5;
			map->s_player.e_orientation = pos;
			line[i] = '0';
		}
		if ((line[i] < '0' || line[i] > '1') && line[i] != '\n')
			return (1);
	}
	if (i > map->width)
		map->width = ft_eval_width(line, i);
	++map->height;
	return (0);
}

int32_t	ft_eval_width(char *line, int32_t i)
{
	if ('\n' == line[i - 1])
		--i;
	return (i);
}

t_orientation	ft_str_to_enum(char *str, t_orientation *pos)
{
	static const char	orientation[N_ORIENTATION][2] = {
		"N", "S", "W", "E"
	};

	*pos = 0;
	while (*pos < N_ORIENTATION)
	{
		if (0 == ft_strncmp(orientation[*pos], str, 1))
			return (*pos);
		++(*pos);
	}
	return (*pos);
}

static t_map_exception	ft_format_map(t_map *map, char **tmp_map)
{
	t_map_exception ret;

	ret = NO_MAP_EXCEPTION;
	if (N_ORIENTATION == map->s_player.e_orientation
		|| ft_resize_map(map, tmp_map) != 0
		|| ft_check_border(map, *tmp_map) != 0)
		ret = ELEMENT_ERROR;

	free(*tmp_map);
	return (ret);
}

uint8_t	ft_resize_map(t_map *map, char **tmp_map)
{
	const size_t	len = ((size_t)(map->width * map->height + 1));
	size_t			i;
	size_t			j;
	char			*resized_line;

	i = 0;
	resized_line = ft_calloc(len, sizeof(char));
	while (NULL != resized_line && *(*tmp_map + i) != '\0')
	{
		j = ft_len_till(*tmp_map + i, '\n');
		ft_strlcat(resized_line, *tmp_map + i, ft_strlen(resized_line) + j + 1);
		ft_memset(&resized_line[ft_strlen(resized_line)], '1', (size_t)map->width - j);
		i += j + 1;
	}
	free(*tmp_map);
	*tmp_map = resized_line;
	return (NULL == tmp_map);
}

size_t	ft_len_till(char *str, char c)
{
	const char	*s = str;

	while (*s != '\0')
	{
		if (c == *s)
			break ;
		++s;
	}
	return ((size_t)(s - str));
}

uint8_t	ft_check_border(t_map *map, char *tmp_map)
{
	const int32_t map_size = map->width * map->height;
	const t_parse_border parse_border[4] = {
			{0, 1, map->width}, //front
			{0, map->width, map_size - map->width}, //left
			{map->width - 1, map->width, map_size}, // right
			{map_size - map->width, 1, map_size}, // bottom
	};
	int32_t from;
	int32_t to;
	int32_t i;

	i = 0;
	while (i < 4)
	{
		from = parse_border[i].from;
		to = parse_border[i].to;
		while (from < to)
		{
			if (tmp_map[from] != '1')
				return (1);
			from += parse_border[i].each;
		}
		++i;
	}
	return (0);
}
