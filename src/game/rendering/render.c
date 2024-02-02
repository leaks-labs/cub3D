/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:02 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:34:02 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "game.h"

int				ft_render(t_game *game);
static void		ft_raycast_init(t_game *game, int x);
static void		ft_raycast_side_dist_init(t_player *pl, t_raycast *rc);
static double	ft_get_ray_len(t_raycast *rc, t_map *map);
static void		ft_update_moves(t_game *game);

int	ft_render(t_game *game)
{
	int	current_x;

	ft_draw_text_env(game, &game->map->s_player);
	current_x = 0;
	while (current_x < game->graphx->s_window.s_image.width)
	{
		ft_raycast_init(game, current_x);
		game->s_raycast.wall_dist = ft_get_ray_len(&game->s_raycast, game->map);
		ft_draw(game, current_x);
		++current_x;
	}
	ft_update_moves(game);
	ft_refresh(game);
	if (game->show_minimap == true)
	{
		ft_draw_map(&game->map->s_mini_map, game->map);
		ft_minimap_zoom(game);
		ft_refresh_mini_map(game);
	}
	return (0);
}

static void	ft_raycast_init(t_game *game, int x)
{
	const double	screen_w = (double)(game->graphx->s_window.s_image.width);

	game->s_raycast.camera_x = 2 * x / screen_w - 1;
	game->s_raycast.s_ray_dir.x = game->map->s_player.s_dir.x \
					+ game->map->s_player.s_plane.x * game->s_raycast.camera_x;
	game->s_raycast.s_ray_dir.y = game->map->s_player.s_dir.y \
					+ game->map->s_player.s_plane.y * game->s_raycast.camera_x;
	game->s_raycast.s_map_tmp.x = (int)game->map->s_player.s_pos.x;
	game->s_raycast.s_map_tmp.y = (int)game->map->s_player.s_pos.y;
	game->s_raycast.s_delta_dist.x = fabs(1.0 / game->s_raycast.s_ray_dir.x);
	game->s_raycast.s_delta_dist.y = fabs(1.0 / game->s_raycast.s_ray_dir.y);
	ft_raycast_side_dist_init(&game->map->s_player, &game->s_raycast);
}

static void	ft_raycast_side_dist_init(t_player *pl, t_raycast *rc)
{
	if (rc->s_ray_dir.x < 0)
	{
		rc->s_step.x = -1;
		rc->s_side_dist.x = (pl->s_pos.x - rc->s_map_tmp.x) \
							* rc->s_delta_dist.x;
	}
	else
	{
		rc->s_step.x = 1;
		rc->s_side_dist.x = (rc->s_map_tmp.x + 1.0 - pl->s_pos.x) \
							* rc->s_delta_dist.x;
	}
	if (rc->s_ray_dir.y < 0)
	{
		rc->s_step.y = -1;
		rc->s_side_dist.y = (pl->s_pos.y - rc->s_map_tmp.y) \
							* rc->s_delta_dist.y;
	}
	else
	{
		rc->s_step.y = 1;
		rc->s_side_dist.y = (rc->s_map_tmp.y + 1.0 - pl->s_pos.y) \
							* rc->s_delta_dist.y;
	}
}

static double	ft_get_ray_len(t_raycast *rc, t_map *map)
{
	bool	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->s_side_dist.x < rc->s_side_dist.y)
		{
			rc->s_side_dist.x += rc->s_delta_dist.x;
			rc->s_map_tmp.x += rc->s_step.x;
			rc->side_touched = TOUCH_X_AXIS;
		}
		else
		{
			rc->s_side_dist.y += rc->s_delta_dist.y;
			rc->s_map_tmp.y += rc->s_step.y;
			rc->side_touched = TOUCH_Y_AXIS;
		}
		hit = ft_isawall_grid(map, rc->s_map_tmp.x, rc->s_map_tmp.y);
	}
	if (rc->side_touched == TOUCH_X_AXIS)
		return (rc->s_side_dist.x - rc->s_delta_dist.x);
	return (rc->s_side_dist.y - rc->s_delta_dist.y);
}

static void	ft_update_moves(t_game *game)
{
	ft_move_back_forth(game);
	ft_move_left_right(game);
	ft_rotate_left_right(game);
	ft_look_up_down(game);
	ft_rotate_mouse(game);
}
