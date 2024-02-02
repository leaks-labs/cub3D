/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:53 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:34:42 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "game.h"

void		ft_draw_text_env(t_game *game, t_player *pl);
static void	ft_scan_one_line(t_game *game, t_env *env);
static void	ft_init_coord_and_step(t_env *env, double row_dist, t_game *game);
static void	ft_print_pixel_on_line(t_env *env, t_image *tex);

void	ft_draw_text_env(t_game *game, t_player *pl)
{
	t_env	s_env;
	int		max_y;

	max_y = game->graphx->s_window.s_image.height;
	s_env.s_dst_pix.y = 0;
	s_env.dst_img = &game->graphx->s_window.s_image;
	s_env.tex_ceiling = &game->map->texture[CEILING].image[0];
	s_env.tex_floor = &game->map->texture[FLOOR].image[0];
	if (s_env.tex_ceiling->mlx_img == NULL)
		s_env.s_dst_pix.y = game->screen_center;
	if (s_env.tex_floor->mlx_img == NULL)
		max_y = game->screen_center;
	s_env.s_ray_dir_l.x = pl->s_dir.x - pl->s_plane.x;
	s_env.s_ray_dir_l.y = pl->s_dir.y - pl->s_plane.y;
	s_env.s_ray_dir_r.x = pl->s_dir.x + pl->s_plane.x;
	s_env.s_ray_dir_r.y = pl->s_dir.y + pl->s_plane.y;
	while (s_env.s_dst_pix.y < max_y)
	{
		ft_scan_one_line(game, &s_env);
		s_env.s_dst_pix.y++;
	}
}

static void	ft_scan_one_line(t_game *game, t_env *env)
{
	const double	pos_z = game->graphx->s_window.s_image.height * 0.5;
	int				p;
	double			row_distance;
	t_image			*actual_tex;

	actual_tex = env->tex_floor;
	p = env->s_dst_pix.y - game->screen_center;
	if (env->s_dst_pix.y < game->screen_center)
	{
		actual_tex = env->tex_ceiling;
		p = -p;
	}
	row_distance = pos_z / p;
	ft_init_coord_and_step(env, row_distance, game);
	env->s_dst_pix.x = 0;
	while (env->s_dst_pix.x < game->graphx->s_window.s_image.width)
	{
		ft_print_pixel_on_line(env, actual_tex);
		env->s_dst_pix.x++;
	}
}

static void	ft_init_coord_and_step(t_env *env, double row_dist, t_game *game)
{
	env->s_step.x = row_dist * (env->s_ray_dir_r.x - env->s_ray_dir_l.x) \
					/ game->graphx->s_window.s_image.width;
	env->s_step.y = row_dist * (env->s_ray_dir_r.y - env->s_ray_dir_l.y) \
					/ game->graphx->s_window.s_image.width;
	env->s_coord.x = game->map->s_player.s_pos.x + \
					row_dist * env->s_ray_dir_l.x;
	env->s_coord.y = game->map->s_player.s_pos.y + \
					row_dist * env->s_ray_dir_l.y;
}

static void	ft_print_pixel_on_line(t_env *env, t_image *tex)
{
	env->s_grid_coord.x = (int)(env->s_coord.x);
	env->s_grid_coord.y = (int)(env->s_coord.y);
	env->s_src_pix.x = (int)(tex->width \
						* (env->s_coord.x - env->s_grid_coord.x)) \
						& (tex->width - 1);
	env->s_src_pix.y = (int)(tex->height \
						* (env->s_coord.y - env->s_grid_coord.y)) \
						& (tex->height - 1);
	env->s_coord.x += env->s_step.x;
	env->s_coord.y += env->s_step.y;
	ft_pixel_cpy(tex, env->dst_img, &env->s_src_pix, &env->s_dst_pix);
}
