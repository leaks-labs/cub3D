/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:43 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:23:44 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_rotate(t_game *game, double factor);
void	ft_rotate_left_right(t_game *game);
void	ft_look_up_down(t_game *game);
void	ft_rescale_ver_view(int *screen_center, int window_height);
void	ft_rescale_angle(double *angle);

void	ft_rotate(t_game *game, double factor)
{
	const double	cos_fact = cos(ROTATION_VELOCITY * factor);
	const double	sin_fact = sin(ROTATION_VELOCITY * factor);
	const double	old_dir_x = game->map->s_player.s_dir.x;
	const double	old_plane_x = game->map->s_player.s_plane.x;

	game->map->s_player.s_dir.x = game->map->s_player.s_dir.x * cos_fact \
								- game->map->s_player.s_dir.y * sin_fact;
	game->map->s_player.s_dir.y = old_dir_x * sin_fact \
								+ game->map->s_player.s_dir.y * cos_fact;
	game->map->s_player.s_plane.x = game->map->s_player.s_plane.x * cos_fact \
									- game->map->s_player.s_plane.y * sin_fact;
	game->map->s_player.s_plane.y = old_plane_x * sin_fact \
									+ game->map->s_player.s_plane.y * cos_fact;
}

void	ft_rotate_left_right(t_game *game)
{
	if ((game->bit_switch & BIT_KEY_ARROW_LEFT) != 0)
	{
		ft_rotate(game, -1);
		game->map->s_mini_map.angle -= ROTATION_VELOCITY;
		ft_rescale_angle(&game->map->s_mini_map.angle);
	}
	if ((game->bit_switch & BIT_KEY_ARROW_RIGHT) != 0)
	{
		ft_rotate(game, 1);
		game->map->s_mini_map.angle += ROTATION_VELOCITY;
		ft_rescale_angle(&game->map->s_mini_map.angle);
	}
}

void	ft_look_up_down(t_game *game)
{
	if ((game->bit_switch & BIT_KEY_ARROW_UP) != 0)
		game->screen_center += VER_VIEW_VELOCITY;
	if ((game->bit_switch & BIT_KEY_ARROW_DOWN) != 0)
		game->screen_center -= VER_VIEW_VELOCITY;
	ft_rescale_ver_view(&game->screen_center, \
						game->graphx->s_window.s_image.height);
}

void	ft_rescale_ver_view(int *screen_center, int window_height)
{
	if (*screen_center < 10)
		*screen_center = 10;
	else if (*screen_center >= window_height - 10)
		*screen_center = window_height - 10;
}

void	ft_rescale_angle(double *angle)
{
	if (*angle < 0)
		*angle += RAD_MAX;
	else if (*angle >= RAD_MAX)
		*angle -= RAD_MAX;
}
