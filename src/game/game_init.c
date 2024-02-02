/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:32 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:23:33 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map);
static void	ft_adapt_vectors(t_map *map);
static void	ft_init_minimap(t_mini_map *mini_map);

void	ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map)
{
	game->map = map;
	game->graphx = graphx;
	game->s_mouse.mouse_tracked = false;
	game->s_mouse.rot_mouse_left_right = 0.0;
	game->s_mouse.rot_mouse_up_down = 0;
	game->show_minimap = false;
	game->bit_switch = 0;
	map->s_player.s_dir.x = 0;
	map->s_player.s_dir.y = 0;
	map->s_player.s_plane.x = 0;
	map->s_player.s_plane.y = 0;
	ft_adapt_vectors(game->map);
	ft_init_minimap(&game->map->s_mini_map);
}

static void	ft_adapt_vectors(t_map *map)
{
	if (map->s_player.e_orientation == EAST)
	{
		map->s_player.s_dir.x = 1;
		map->s_player.s_plane.y = FOV_FACTOR;
		map->s_mini_map.angle = RAD_EAST;
	}
	else if (map->s_player.e_orientation == WEST)
	{
		map->s_player.s_dir.x = -1;
		map->s_player.s_plane.y = -FOV_FACTOR;
		map->s_mini_map.angle = RAD_WEST;
	}
	if (map->s_player.e_orientation == NORTH)
	{
		map->s_player.s_dir.y = -1;
		map->s_player.s_plane.x = FOV_FACTOR;
		map->s_mini_map.angle = RAD_NORTH;
	}
	else if (map->s_player.e_orientation == SOUTH)
	{
		map->s_player.s_dir.y = 1;
		map->s_player.s_plane.x = -FOV_FACTOR;
		map->s_mini_map.angle = RAD_SOUTH;
	}
}

static void	ft_init_minimap(t_mini_map *mini_map)
{
	mini_map->empty_color = EMPTY_COLOR_MAP;
	mini_map->wall_color = WALL_COLOR_MAP;
	mini_map->units = MINI_MAP_PIX_PER_CELL;
	mini_map->steps = 1.0 / mini_map->units;
}
