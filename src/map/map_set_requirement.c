/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set_requirement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:11 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:45:32 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <unistd.h>
#include "utils.h"

uint8_t			ft_set_args(t_map *map, const t_dictionary *lexic, char *args);
static uint8_t	ft_set_path(t_map *map, const t_dictionary *lexic, char *args);
static uint8_t	ft_set_rgb(t_map *map, const t_dictionary *lexic, char *args);

uint8_t	ft_set_args(t_map *map, const t_dictionary *lexic, char *args)
{
	if (PATH_ERROR == lexic->exception)
		return (ft_set_path(map, lexic, args));
	return (ft_set_rgb(map, lexic, args));
}

static uint8_t	ft_set_path(t_map *map, const t_dictionary *lexic, char *args)
{
	const size_t	len = ft_strlen(args);
	int32_t			fd;

	if ('\n' == args[len - 1])
		args[len - 1] = '\0';
	if (len >= PATH_MAX || 1 == ft_open_file(args, &fd))
		return (1);
	close(fd);
	ft_strlcpy(map->texture[lexic->element].path[lexic->orientation], \
				args, len);
	return (0);
}

static uint8_t	ft_set_rgb(t_map *map, const t_dictionary *lexic, char *args)
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
	map->texture[lexic->element].rgb[lexic->orientation] \
		= ((rgb_val[0] & 0x0ff) << 16) \
		| ((rgb_val[1] & 0x0ff) << 8) \
		| (rgb_val[2] & 0x0ff);
	return (ft_freef("%P", rgb), 0);
}
