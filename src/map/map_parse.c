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
	if (map_exception >= REQUIREMENT_ERROR && map_exception <= RGB_ERROR) {
		printf("here\n");
		return (close(fd), map_exception);
	}
	if (ELEMENT_ERROR == ft_check_map(map, fd))
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

static t_map_exception	ft_check_requirement(t_map *map, int32_t fd, size_t i)
{
	static const char dictionary[N_REQUIREMENT][REQUIREMENT_LEN] = {
			REQUIREMENT_NORTH_TEXTURE,REQUIREMENT_SOUTH_TEXTURE,
			REQUIREMENT_WEST_TEXTURE,REQUIREMENT_EAST_TEXTURE,
			REQUIREMENT_FLOOR_RGB,REQUIREMENT_CEILING_RGB
	};
	char **requirement;
	char *line;

	ft_read_line(&line, fd);
	requirement = ft_split(line, ' ');
	if (requirement == NULL || requirement[1] == NULL || ft_strcmp(dictionary[i], requirement[0]) != 0)
		return (ft_freef("%p, %P", line, requirement), REQUIREMENT_ERROR);
	if (ft_check_path(requirement[i], map) == 0)
		;
	ft_freef("%p, %P", line, requirement);
	if (i < N_REQUIREMENT && ft_check_requirement(map, fd, ++i) == 3)
		return (REQUIREMENT_ERROR);
	return (NO_MAP_EXCEPTION);
}


static t_map_exception	ft_check_map( t_map *map, int32_t fd)
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