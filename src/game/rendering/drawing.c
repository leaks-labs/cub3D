/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:59 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:24:00 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "game.h"

void		ft_draw(t_game *game, int x);
static void	ft_draw_init(t_game *game, t_draw *draw, int x);
static void	ft_draw_ceiling(t_draw *draw, t_map *map);
static void	ft_draw_floor(t_draw *draw, t_map *map, int window_height);

void	ft_draw(t_game *game, int x)
{
	t_draw	s_draw;

	ft_draw_init(game, &s_draw, x);
	if (game->map->texture[CEILING].image->mlx_img == NULL)
		ft_draw_ceiling(&s_draw, game->map);
	ft_draw_wall(game, &s_draw);
	if (game->map->texture[FLOOR].image->mlx_img == NULL)
		ft_draw_floor(&s_draw, game->map, \
						game->graphx->s_window.s_image.height);
}

static void	ft_draw_init(t_game *game, t_draw *draw, int x)
{
	draw->line_height = (int)(game->graphx->s_window.s_image.height \
								/ game->s_raycast.wall_dist);
	draw->draw_start = game->screen_center - draw->line_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = game->screen_center + draw->line_height / 2;
	if (draw->draw_end >= game->graphx->s_window.s_image.height)
		draw->draw_end = game->graphx->s_window.s_image.height - 1;
	draw->s_dst_pix.x = x;
	draw->s_dst_pix.y = 0;
	draw->dst_img = &game->graphx->s_window.s_image;
}

static void	ft_draw_ceiling(t_draw *draw, t_map *map)
{
	if (draw->draw_start < 0)
		return ;
	draw->s_dst_pix.y = 0;
	draw->s_dst_pix.colour = map->texture[CEILING].rgb[0];
	while (draw->s_dst_pix.y < draw->draw_start)
	{
		ft_pixel_put(draw->dst_img, &draw->s_dst_pix);
		draw->s_dst_pix.y++;
	}
}

static void	ft_draw_floor(t_draw *draw, t_map *map, int window_height)
{
	if (draw->draw_end >= window_height - 1)
		return ;
	draw->s_dst_pix.y = draw->draw_end + 1;
	draw->s_dst_pix.colour = map->texture[FLOOR].rgb[0];
	while (draw->s_dst_pix.y < window_height)
	{
		ft_pixel_put(draw->dst_img, &draw->s_dst_pix);
		draw->s_dst_pix.y++;
	}
}
