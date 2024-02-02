/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:18 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:45:52 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include "utils.h"

t_map_exception			ft_verify_map(t_map *map, char **tmp_map, int32_t fd, \
										bool empty);
uint8_t					ft_is_valid_map(t_map *map, char *line);
static t_orientation	ft_str_to_enum(char *str, t_orientation *pos);
static int32_t			ft_eval_width(char *line, int32_t i);

t_map_exception	ft_verify_map(t_map *map, char **tmp_map, int32_t fd, \
								bool empty)
{
	char	*line;
	void	*ptr_cpy;

	if (NULL == *tmp_map)
		return (ELEMENT_ERROR);
	if (NULL == ft_read_line(&line, fd, '\0'))
		return (NO_MAP_EXCEPTION);
	if ('\n' == *line)
		return (free(line), ft_verify_map(map, tmp_map, fd, true));
	if (true == empty || ft_is_valid_map(map, line))
		return (ft_freef("%p, %p", *tmp_map, line), ELEMENT_ERROR);
	ptr_cpy = *tmp_map;
	*tmp_map = ft_join(2, *tmp_map, line);
	ft_freef("%p, %p", ptr_cpy, line);
	return (ft_verify_map(map, tmp_map, fd, empty));
}

uint8_t	ft_is_valid_map(t_map *map, char *line)
{
	int32_t			i;
	t_orientation	e_pos;

	i = -1;
	while (line[++i] != '\0')
	{
		if (' ' == line[i])
			line[i] = '1';
		if (N_ORIENTATION == map->s_player.e_orientation
			&& ft_str_to_enum(&line[i], &e_pos) != N_ORIENTATION)
		{
			map->s_player.s_pos.x = i + 0.5;
			map->s_player.s_pos.y = map->height + 0.5;
			map->s_player.e_orientation = e_pos;
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

static t_orientation	ft_str_to_enum(char *str, t_orientation *pos)
{
	static const char	orientation[N_ORIENTATION][2] = {\
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

static int32_t	ft_eval_width(char *line, int32_t i)
{
	if ('\n' == line[i - 1])
		--i;
	return (i);
}
