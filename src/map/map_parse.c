#include "map.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

static uint8_t			ft_check_extension(char *str, char *ext);
static uint8_t			ft_open_file(char *file, int32_t *fd);
static t_map_exception	ft_check_requirement(int32_t fd, t_map *map);
static t_map_exception	ft_check_map(int32_t fd, t_map *map);
//static t_map_exception	ft_read_file(int32_t fd);

char *ft_read_line(char **str, int32_t fd);

t_map_exception ft_parse_map(char *file, t_map *map)
{
	t_map_exception	map_exception;
	int32_t			fd;

	if (1 == ft_check_extension(file, (char *)".pub"))
		return (EXTENSION_ERROR);
	if (1 == ft_open_file(file, &fd))
		return (OPEN_ERROR);
	map_exception = ft_check_requirement(fd, map);
	if (map_exception >= REQUIREMENT_ERROR && map_exception <= RGB_ERROR) {
		printf("here\n");
		return (close(fd), map_exception);
	}
	if (ELEMENT_ERROR == ft_check_map(fd, map))
		return (ELEMENT_ERROR);
	/* set map */
	close(fd);
	return (map_exception);
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

static t_map_exception	ft_check_requirement(int32_t fd, t_map *map)
{
	const t_dictionary dictionary[N_REQUIREMENT] = {
			{REQUIREMENT_NORTH_TEXTURE, 2},
			{REQUIREMENT_SOUTH_TEXTURE, 2},
			{REQUIREMENT_WEST_TEXTURE, 2},
			{REQUIREMENT_EAST_TEXTURE, 2},
			{REQUIREMENT_FLOOR_RGB, 1},
			{REQUIREMENT_CEILING_RGB, 1},
	};
	size_t i;
	char **requirement;
	char *line;

	i = 0;
	while (ft_read_line(&line, fd) && i < 6)
	{
		requirement = ft_split(line, ' ');
		if (requirement == NULL || requirement[1] == NULL)
			return (REQUIREMENT_ERROR);
		printf("%s.\n", requirement[0]);
		if (ft_strncmp(dictionary[i].requirement, requirement[0], dictionary[i].len) != 0)
		{
			printf("%s, %s\n", dictionary[i].requirement, requirement[0]);
			return (REQUIREMENT_ERROR);
		}
		++i;
	}
	(void)map;
	return (NO_MAP_EXCEPTION);
}

static t_map_exception	ft_check_map(int32_t fd, t_map *map)
{
	(void)fd;
	(void)map;
	return (NO_MAP_EXCEPTION);
}

char *ft_read_line(char **str, int32_t fd)
{
	*str = ft_get_next_line(fd);
	if (**str == '\n')
	{
		free(*str);
		ft_read_line(str, fd);
	}
	return	(*str);
}