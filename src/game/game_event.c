/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:29 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:23:30 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_escape(t_game *game);
void	ft_minimap_zoom(t_game *game);
void	ft_rotate_mouse(t_game *game);

void	ft_escape(t_game *game)
{
	ft_on_destroy(game);
}

void	ft_minimap_zoom(t_game *game)
{
	if (game->show_minimap == false)
		return ;
	if ((game->bit_switch & BIT_KEY_I) && !(game->bit_switch & BIT_KEY_O))
		game->map->s_mini_map.units += M_MAP_ZOOM_SPEED;
	else if (!(game->bit_switch & BIT_KEY_I) && (game->bit_switch & BIT_KEY_O))
		game->map->s_mini_map.units -= M_MAP_ZOOM_SPEED;
	else
		return ;
	if (game->map->s_mini_map.units < 10)
		game->map->s_mini_map.units = 10;
	else if (game->map->s_mini_map.units > 200)
		game->map->s_mini_map.units = 200;
	game->map->s_mini_map.steps = 1.0 / game->map->s_mini_map.units;
}

void	ft_rotate_mouse(t_game *game)
{
	const double	old_rot_left_right = game->s_mouse.rot_mouse_left_right;
	const int		old_rot_up_down = game->s_mouse.rot_mouse_up_down;

	game->screen_center += old_rot_up_down;
	ft_rescale_ver_view(&game->screen_center, \
						game->graphx->s_window.s_image.height);
	game->s_mouse.rot_mouse_up_down -= old_rot_up_down;
	ft_rotate(game, -old_rot_left_right / 8);
	game->map->s_mini_map.angle += (-old_rot_left_right / 8) \
									* ROTATION_VELOCITY;
	ft_rescale_angle(&game->map->s_mini_map.angle);
	game->s_mouse.rot_mouse_left_right -= old_rot_left_right;
}
