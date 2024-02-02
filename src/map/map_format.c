/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:55 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:45:15 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include "utils.h"

t_map_exception	ft_format_map(t_map *map, char **tmp_map);
static uint8_t	ft_resize_map(t_map *map, char **tmp_map);
static uint8_t	ft_check_border(t_map *map, char *tmp_map);
static uint8_t	ft_map_to_int(t_map *map, char *tmp_map);

t_map_exception	ft_format_map(t_map *map, char **tmp_map)
{
	t_map_exception	e_ret;

	e_ret = NO_MAP_EXCEPTION;
	if (N_ORIENTATION == map->s_player.e_orientation \
		|| ft_resize_map(map, tmp_map) != 0 \
		|| ft_check_border(map, *tmp_map) != 0 \
		|| ft_map_to_int(map, *tmp_map) != 0)
		e_ret = ELEMENT_ERROR;
	free(*tmp_map);
	return (e_ret);
}

static uint8_t	ft_resize_map(t_map *map, char **tmp_map)
{
	const size_t	len = (size_t)map->width * (size_t)map->height + 1;
	const size_t	tmp_len = ft_strlen(*tmp_map);
	char			*resized_line;
	size_t			i;
	size_t			j;

	i = 0;
	resized_line = ft_calloc(len, sizeof(char));
	while (NULL != resized_line && *(*tmp_map + i) != '\0')
	{
		j = ft_len_till(*tmp_map + i, '\n');
		ft_strlcat(resized_line, *tmp_map + i, \
					ft_strlen(resized_line) + j + 1);
		ft_memset(&resized_line[ft_strlen(resized_line)], '1', \
					(size_t)map->width - j);
		i += j + 1;
		if (i > tmp_len)
			--i;
	}
	free(*tmp_map);
	*tmp_map = resized_line;
	return (NULL == tmp_map);
}

static uint8_t	ft_check_border(t_map *map, char *tmp_map)
{
	const size_t			map_size = (size_t)map->width * (size_t)map->height;
	const t_parse_border	parse_border[4] = {\
			{0, 1, (size_t)map->width}, \
			{0, (size_t)map->width, map_size - (size_t)map->width}, \
			{(size_t)(map->width - 1), (size_t)map->width, map_size}, \
			{map_size - (size_t)map->width, 1, map_size}, \
	};
	size_t					from;
	size_t					to;
	size_t					i;

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

static uint8_t	ft_map_to_int(t_map *map, char *tmp_map)
{
	const size_t	len = (size_t)map->width * (size_t)map->height;
	size_t			i;

	map->grid = ft_calloc(len, sizeof(t_element));
	i = 0;
	while (map->grid != NULL && i < len)
	{
		map->grid[i] = (t_element)(tmp_map[i] - '0');
		++i;
	}
	return (NULL == map->grid);
}
