/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:02 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 18:15:31 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"
#include <unistd.h>

t_map_exception	ft_parse_map(const char *file, t_map *map);
static void		ft_map_set_default(t_map *map);

t_map_exception	ft_parse_map(const char *file, t_map *map)
{
	char			*tmp_map;
	t_map_exception	e_map_exception;
	int32_t			fd;

	if (1 == ft_check_extension(file, ".cub"))
		return (EXTENSION_ERROR);
	if (1 == ft_open_file(file, &fd))
		return (OPEN_ERROR);
	ft_map_set_default(map);
	e_map_exception = ft_check_requirement(map, &tmp_map, fd, 0);
	if (!(e_map_exception >= REQUIREMENT_ERROR && e_map_exception <= RGB_ERROR))
		if (ELEMENT_ERROR == ft_verify_map(map, &tmp_map, fd, false) \
			|| ELEMENT_ERROR == ft_format_map(map, &tmp_map))
			e_map_exception = ELEMENT_ERROR;
	close(fd);
	return (e_map_exception);
}

void	ft_map_set_default(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->s_player.e_orientation = N_ORIENTATION;
	map->texture[FLOOR].path[0][0] = '\0';
	map->texture[CEILING].path[0][0] = '\0';
}
