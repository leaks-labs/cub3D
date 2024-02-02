/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:38 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:23:39 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_move_back_forth(t_game *game);
void	ft_move_left_right(t_game *game);

void	ft_move_back_forth(t_game *game)
{
	double	new_x_real;
	double	new_y_real;
	int		new_x_grid;
	int		new_y_grid;
	int		dir;

	if ((game->bit_switch & BIT_KEY_W) && !(game->bit_switch & BIT_KEY_S))
		dir = 1;
	else if (!(game->bit_switch & BIT_KEY_W) && (game->bit_switch & BIT_KEY_S))
		dir = -1;
	else
		return ;
	new_x_real = game->map->s_player.s_pos.x \
					+ game->map->s_player.s_dir.x * MOVEMENT_VELOCITY * dir;
	new_y_real = game->map->s_player.s_pos.y \
					+ game->map->s_player.s_dir.y * MOVEMENT_VELOCITY * dir;
	new_x_grid = (int)new_x_real;
	new_y_grid = (int)new_y_real;
	if (!ft_isawall_grid(game->map, new_x_grid, \
						(int)game->map->s_player.s_pos.y))
		game->map->s_player.s_pos.x = new_x_real;
	if (!ft_isawall_grid(game->map, (int)game->map->s_player.s_pos.x, \
							new_y_grid))
		game->map->s_player.s_pos.y = new_y_real;
}

void	ft_move_left_right(t_game *game)
{
	double	new_x_real;
	double	new_y_real;
	int		new_x_grid;
	int		new_y_grid;
	int		dir;

	if ((game->bit_switch & BIT_KEY_A) && !(game->bit_switch & BIT_KEY_D))
		dir = -1;
	else if (!(game->bit_switch & BIT_KEY_A) && (game->bit_switch & BIT_KEY_D))
		dir = 1;
	else
		return ;
	new_x_real = game->map->s_player.s_pos.x \
					+ game->map->s_player.s_plane.x * MOVEMENT_VELOCITY * dir;
	new_y_real = game->map->s_player.s_pos.y \
					+ game->map->s_player.s_plane.y * MOVEMENT_VELOCITY * dir;
	new_x_grid = (int)new_x_real;
	new_y_grid = (int)new_y_real;
	if (!ft_isawall_grid(game->map, new_x_grid, \
						(int)game->map->s_player.s_pos.y))
		game->map->s_player.s_pos.x = new_x_real;
	if (!ft_isawall_grid(game->map, (int)game->map->s_player.s_pos.x, \
							new_y_grid))
		game->map->s_player.s_pos.y = new_y_real;
}
