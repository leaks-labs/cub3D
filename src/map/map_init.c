/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:59 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:25:00 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

uint8_t	ft_init_map(char *file, t_map *map);

uint8_t	ft_init_map(char *file, t_map *map)
{
	return (ft_throw_map_exception(ft_parse_map(file, map)));
}
