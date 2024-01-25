#include "map.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

static uint8_t			ft_check_extension(char *str, char *ext);
static uint8_t			ft_open_file(char *file, int32_t *fd);
static t_map_exception	ft_check_requirement(t_map *map, char **tmp_map, int32_t fd, size_t i);
static t_map_exception	ft_check_map(t_map *map, char *tmp_map, int32_t fd);

char *ft_read_line(char **str, int32_t fd);
uint8_t ft_set_args(t_map *map, const t_dictionary *lexic, char *args);
uint8_t ft_set_path(t_map *map, const t_dictionary *lexic, char *args);
uint8_t ft_set_rgb(t_map *map, const t_dictionary *lexic, char *args);
size_t ft_n_occurence(char *str, char c);

uint8_t ft_rule_match(t_dictionary *lexic, char *rule, size_t *index);
uint8_t ft_is_match(t_dictionary *lexic, char **tmp_map, char *line, char *rule);
t_dictionary *ft_set_lexic(t_dictionary	**lexic);

t_map_exception ft_parse_map(char *file, t_map *map)
{
	t_map_exception	map_exception;
	char			*<< test "">>;
	int32_t			fd;

	if (1 == ft_check_extension(file, (char *)".pub"))
		return (EXTENSION_ERROR);
	if (1 == ft_open_file(file, &fd))
		return (OPEN_ERROR);
	map_exception = ft_check_requirement(map, &tmp_map, fd, 0);
	if (map_exception >= REQUIREMENT_ERROR && map_exception <= RGB_ERROR)
		return (close(fd), map_exception);
	if (ELEMENT_ERROR == ft_check_map(map, tmp_map, fd))
		return (close(fd), ELEMENT_ERROR);
	close(fd);
	return (NO_MAP_EXCEPTION);
}

uint8_t ft_check_extension(char *str, char *ext)
{
	size_t i;

	i = ft_strlen(str);
	while (str[i] != '.' && i != 0)
		--i;
	return (ft_strcmp(&str[i], ext) != 0);
}

uint8_t ft_open_file(char *file, int32_t *fd)
{
	*fd = open(file, O_RDONLY);
	return (-1 == *fd);
}

static t_map_exception	ft_check_requirement(t_map *map, char **tmp_map, int32_t fd, size_t i)
{
	static t_dictionary	*lexic;
	size_t 				index;
	char				**args;
	char				*line;
	t_map_exception		ret;

	if (0 == i && NULL == ft_set_lexic(&lexic))
		return (REQUIREMENT_ERROR);
	ft_read_line(&line, fd);
	args = ft_split(line, ' ');
	if (ft_dptrlen(args) != 2
		|| ft_rule_match(lexic, args[0], &index) != 0)
	{
		ret = NO_MAP_EXCEPTION;
		if (NULL == args || ft_is_match(lexic, tmp_map, line, args[0]) != 0)
			ret = REQUIREMENT_ERROR;
		return (ft_freef("%p, %p, %P", lexic, line, args), ret);
	}
	if (1 == ft_set_args(map, &lexic[index], args[1]))
		return (ft_freef("%p, %p, %P", lexic, line, args),
				lexic[index].exception);
	ft_freef("%p, %P", line, args);
	return (ft_check_requirement(map, tmp_map, fd, ++i));
}

t_dictionary *ft_set_lexic(t_dictionary	**lexic)
{
	const t_dictionary	tmp_lexic[N_RULE]= {
			{NORTH_TEXTURE, MANDATORY, WALL, NORTH, PATH_ERROR},
			{SOUTH_TEXTURE, MANDATORY,WALL, SOUTH, PATH_ERROR},
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

char *ft_read_line(char **str, int32_t fd)
{
	*str = ft_get_next_line(fd);
	if (*str != NULL && '\n' == **str)
	{
		free(*str);
		ft_read_line(str, fd);
	}
	return	(*str);
}

uint8_t ft_rule_match(t_dictionary *lexic, char *rule, size_t *index)
{
	size_t i;

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

uint8_t ft_is_match(t_dictionary *lexic, char **tmp_map, char *line, char *rule)
{
	size_t i;

	i = 0;
	while (i < N_RULE)
	{
		if (lexic[i].rule_type == MANDATORY || 0 == ft_strcmp(lexic[i].rule, rule))
			return (1);
		++i;
	}
	/* if is range map ret 0 else ret 1 for req_error */
	*tmp_map = ft_strdup(line);
	return (0);
}

uint8_t ft_set_args(t_map *map, const t_dictionary *lexic, char *args)
{
	if (PATH_ERROR == lexic->exception)
		return (ft_set_path(map, lexic, args));
	return (ft_set_rgb(map, lexic, args));
}

uint8_t ft_set_path(t_map *map, const t_dictionary *lexic, char *args)
{
	const size_t len = ft_strlen(args);
	int32_t fd;

	if  ('\n' == args[len - 1])
		args[len - 1] = '\0';
	if (len >= PATH_MAX || 1 == ft_open_file(args, &fd))
		return (1);
	close(fd);
	ft_strlcpy(map->texture[lexic->element].orientation[lexic->orientation],
			   args,
			   len);
	return (0);
}

uint8_t ft_set_rgb(t_map *map, const t_dictionary *lexic, char *args)
{
	char	**rgb;
	size_t	len;
	int32_t	rgb_val[3];
	bool	is_overflow;;

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
	map->texture[lexic->element].RGB[lexic->orientation] =
			((rgb_val[0] & 0x0ff) << 16) | ((rgb_val[1] & 0x0ff) << 8) | (rgb_val[2] & 0x0ff);
	return (ft_freef("%P", rgb), 0);
}

size_t ft_n_occurence(char *str, char c)
{
	size_t i;
	size_t j;

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

static t_map_exception	ft_check_map(t_map *map, char *tmp_map, int32_t fd)
{
	int32_t	len;
	char	*tmp;
	char	*line;

	if (NULL == ft_read_line(&line, fd))
		return (NO_MAP_EXCEPTION);
	if (!ft_is_range_map(line, &len))
		return (ELEMENT_ERROR);
	tmp = tmp_map;
	tmp_map = ft_join(2, tmp_map, line);
	ft_freef("%p, %p", tmp, line);
	if (len > map->width)
		map->width = len;
	++map->height;
	return (ft_check_map(map, tmp_map, fd));
	return (NO_MAP_EXCEPTION);
}

