/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:56 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:33:36 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "game.h"

void					ft_draw_wall(t_game *game, t_draw *draw);
static t_orientation	ft_get_orientation(t_raycast *raycast);
static void				ft_texture_iter(t_draw *draw, t_game *game, \
										t_image *src_img, double wall_x);

void	ft_draw_wall(t_game *game, t_draw *draw)
{
	t_element		e_block_type;
	t_orientation	e_orientation;
	t_image			*src_img;
	double			wall_x;

	e_block_type = game->map->grid[(size_t)game->s_raycast.s_map_tmp.x \
									+ (size_t)game->s_raycast.s_map_tmp.y \
									* (size_t)game->map->width];
	e_orientation = ft_get_orientation(&game->s_raycast);
	src_img = &game->map->texture[e_block_type].image[e_orientation];
	if (game->s_raycast.side_touched == TOUCH_X_AXIS)
		wall_x = game->map->s_player.s_pos.y \
				+ game->s_raycast.wall_dist * game->s_raycast.s_ray_dir.y;
	else
		wall_x = game->map->s_player.s_pos.x \
				+ game->s_raycast.wall_dist * game->s_raycast.s_ray_dir.x;
	wall_x -= floor(wall_x);
	ft_texture_iter(draw, game, src_img, wall_x);
}

static t_orientation	ft_get_orientation(t_raycast *raycast)
{
	t_orientation	e_result;

	e_result = NORTH;
	if (raycast->side_touched == TOUCH_X_AXIS && raycast->s_ray_dir.x < 0)
		e_result = EAST;
	else if (raycast->side_touched == TOUCH_X_AXIS && raycast->s_ray_dir.x >= 0)
		e_result = WEST;
	else if (raycast->side_touched == TOUCH_Y_AXIS && raycast->s_ray_dir.y < 0)
		e_result = SOUTH;
	else if (raycast->side_touched == TOUCH_Y_AXIS && raycast->s_ray_dir.y >= 0)
		e_result = NORTH;
	return (e_result);
}

static void	ft_texture_iter(t_draw *draw, t_game *game, t_image *src_img, \
							double wall_x)
{
	const double	step = 1.0 * src_img->height / draw->line_height;
	t_pixel			s_tex;
	double			tex_pos;

	s_tex.x = (int)(wall_x * (double)(src_img->width));
	if (game->s_raycast.side_touched == TOUCH_X_AXIS \
			&& game->s_raycast.s_ray_dir.x > 0)
		s_tex.x = src_img->width - s_tex.x - 1;
	if (game->s_raycast.side_touched == TOUCH_Y_AXIS \
			&& game->s_raycast.s_ray_dir.y < 0)
		s_tex.x = src_img->width - s_tex.x - 1;
	tex_pos = (draw->draw_start - game->screen_center + draw->line_height / 2) \
				* step;
	draw->s_dst_pix.y = draw->draw_start;
	while (draw->s_dst_pix.y <= draw->draw_end)
	{
		s_tex.y = (int)tex_pos & (src_img->height - 1);
		tex_pos += step;
		ft_pixel_cpy(src_img, draw->dst_img, &s_tex, &draw->s_dst_pix);
		draw->s_dst_pix.y++;
	}
}
