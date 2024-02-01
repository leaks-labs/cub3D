#include "map.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

t_map_exception	ft_parse_map(char *file, t_map *map);
static uint8_t			ft_check_extension(char *str, char *ext);
static uint8_t			ft_open_file(char *file, int32_t *fd);
static char				*ft_read_line(char **str, int32_t fd, char to_skip);
static void				ft_map_set_default(t_map *map);

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
	if (!(map_exception >= REQUIREMENT_ERROR && map_exception <= RGB_ERROR))
		if (ELEMENT_ERROR == ft_check_map(map, &tmp_map, fd, false)
			|| ELEMENT_ERROR == ft_format_map(map, &tmp_map))
			map_exception = ELEMENT_ERROR;
	return (close(fd), map_exception);
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
	map->texture[FLOOR].path[0][0] = '\0';
	map->texture[CEILING].path[0][0] = '\0';
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

