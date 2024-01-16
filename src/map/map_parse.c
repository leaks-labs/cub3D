#include "map.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

static uint8_t			ft_check_extension(char *str, char *ext);
static uint8_t			ft_open_file(char *file, int32_t *fd);
static t_map_exception	ft_check_requirement(t_map *map, int32_t fd, size_t i);
static t_map_exception	ft_check_map( t_map *map, int32_t fd);

uint8_t ft_set_path(t_map *map, t_dictionary lexic, char *args);
uint8_t ft_set_rgb(t_map *map, t_dictionary lexic, char *args);

uint8_t ft_set_args(t_map *map, t_dictionary dictionary, char *args);

char *ft_read_line(char **str, int32_t fd);

t_map_exception ft_parse_map(char *file, t_map *map)
{
	t_map_exception	map_exception;
	int32_t			fd;

	if (1 == ft_check_extension(file, (char *)".pub"))
		return (EXTENSION_ERROR);
	if (1 == ft_open_file(file, &fd))
		return (OPEN_ERROR);
	map_exception = ft_check_requirement(map, fd, 0);
	if (map_exception >= REQUIREMENT_ERROR && map_exception <= RGB_ERROR)
		return (close(fd), map_exception);
	map->grid = NULL;
	if (ELEMENT_ERROR == ft_check_map(map, fd))
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

static t_map_exception	ft_check_requirement(t_map *map, int32_t fd, size_t i)
{
	static const t_dictionary lexic[N_RULE]= {
			{NORTH_TEXTURE, WALL, NORTH, PATH_ERROR},
			{SOUTH_TEXTURE,WALL, SOUTH, PATH_ERROR},
			{WEST_TEXTURE,WALL, WEST, PATH_ERROR},
			{EAST_TEXTURE, WALL, EAST, PATH_ERROR},
			{FLOOR_RGB, FLOOR, 0, RGB_ERROR},
			{CEILING_RGB, CEILING, 0, RGB_ERROR}
	};
	char **args;
	char *line;

	ft_read_line(&line, fd);
	args = ft_split(line, ' ');
	if (ft_dptrlen((const char **)args) != 2 || ft_strcmp(lexic[i].rule, args[0]) != 0) /* modify for cp and fp */
		return (ft_freef("%p, %P", line, args), REQUIREMENT_ERROR);
	if (1 == ft_set_args(map, lexic[i], args[1]))
		return (ft_freef("%p, %P", line, args), lexic[i].exception);
	ft_freef("%p, %P", line, args);
	if (i < N_RULE - 1)
		return (ft_check_requirement(map, fd, ++i));
	return (NO_MAP_EXCEPTION);
}


static t_map_exception	ft_check_map(t_map *map, int32_t fd)
{
	t_element	*tmp;
	size_t		i;
	char		*line;

	if (NULL == ft_read_line(&line, fd))
		return (NO_MAP_EXCEPTION);
	i = 0;
	while (line[i] != '\0')
	{
		if ('\n' == line[i])
		{
			line[i] = '\0';
			break;
		}
		if (' ' == line[i])
			line[i] = '0';
		printf("%c\n", line[i]);
		if (line[i] < '0' || line[i] > '1')
			return (ELEMENT_ERROR);
		++i;
	}
	tmp = map->grid;
	ft_join(2, map->grid, line);
	free (tmp);
	return (ft_check_map(map, fd));
}

char *ft_read_line(char **str, int32_t fd)
{
	*str = ft_get_next_line(fd);
	if (*str != NULL && **str == '\n')
	{
		free(*str);
		ft_read_line(str, fd);
	}
	return	(*str);
}

uint8_t ft_set_args(t_map *map, t_dictionary lexic, char *args)
{
	if (PATH_ERROR == lexic.exception)
		return (ft_set_path(map, lexic, args));
	return (ft_set_rgb(map, lexic, args));
}

uint8_t ft_set_path(t_map *map, t_dictionary lexic, char *args)
{
	const size_t len = ft_strlen(args);
	int32_t fd;

	if  ('\n' == args[len - 1])
		args[len - 1] = '\0';
	if (len >= PATH_MAX || 1 == ft_open_file(args, &fd))
		return (1);
	close(fd);
	ft_strlcpy(map->texture[lexic.element].orientation[lexic.orientation], args, len);
	return (0);
}

uint8_t ft_set_rgb(t_map *map, t_dictionary lexic, char *args)
{
	char	**rgb;
	size_t	len;
	int32_t	rgb_val[3];
	bool	is_overflow;;


	rgb = ft_split(args, ',');
	len = ft_dptrlen((const char **)rgb);
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
	map->texture[lexic.element].RGB[lexic.orientation] =
			((rgb_val[0] & 0x0ff) << 16) | ((rgb_val[1] & 0x0ff) << 8) | (rgb_val[2] & 0x0ff);
	return (ft_freef("%P", rgb), 0);
}

