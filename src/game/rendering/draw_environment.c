#include "render.h"
#include "game.h"

void		ft_draw_text_env(t_game *game, t_player *pl);
static void	ft_scan_one_line(t_game *game, t_env *env);
static void	ft_print_pixel_on_line(t_env *env, int screen_center);

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
	// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
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
	// Vertical position of the camera.
	const double	pos_z = game->graphx->s_window.s_image.height * 0.5;
	int				p;
	double			row_distance;

	// Current y position compared to the center of the screen (the horizon)
	if (env->s_dst_pix.y < game->screen_center)
		p = -(env->s_dst_pix.y - game->screen_center);
	else
		p = env->s_dst_pix.y - game->screen_center;

	// Horizontal distance from the camera to the floor for the current row.
	// 0.5 is the z position exactly in the middle between floor and ceiling.
	row_distance = pos_z / p;

	// calculate the real world step vector we have to add for each x (parallel to camera plane)
	// adding step by step avoids multiplications with a weight in the inner loop
	env->s_step.x = row_distance * (env->s_ray_dir_r.x - env->s_ray_dir_l.x) \
					/ game->graphx->s_window.s_image.width;
	env->s_step.y = row_distance * (env->s_ray_dir_r.y - env->s_ray_dir_l.y) \
					/ game->graphx->s_window.s_image.width;

	// real world coordinates of the leftmost column. This will be updated as we step to the right.
	env->s_coord.x = game->map->s_player.s_pos.x + \
					row_distance * env->s_ray_dir_l.x;
	env->s_coord.y = game->map->s_player.s_pos.y + \
					row_distance * env->s_ray_dir_l.y;

	env->s_dst_pix.x = 0;
	while (env->s_dst_pix.x < game->graphx->s_window.s_image.width)
	{
		ft_print_pixel_on_line(env, game->screen_center);
		env->s_dst_pix.x++;
	}
}

static void	ft_print_pixel_on_line(t_env *env, int screen_center)
{
	// the cell coord is simply got from the integer parts of floorX and floorY
	env->s_grid_coord.x = (int)(env->s_coord.x);
	env->s_grid_coord.y = (int)(env->s_coord.y);

	// get the texture coordinate from the fractional part
	env->s_src_pix.x = (int)(env->tex_ceiling->width \
						* (env->s_coord.x - env->s_grid_coord.x)) \
						& (env->tex_ceiling->width - 1);
	env->s_src_pix.y = (int)(env->tex_ceiling->height \
						* (env->s_coord.y - env->s_grid_coord.y)) \
						& (env->tex_ceiling->height - 1);

	env->s_coord.x += env->s_step.x;
	env->s_coord.y += env->s_step.y;

	if (env->s_dst_pix.y < screen_center)
		ft_pixel_cpy(env->tex_ceiling, env->dst_img, \
					&env->s_src_pix, &env->s_dst_pix);
	else
		ft_pixel_cpy(env->tex_floor, env->dst_img, \
					&env->s_src_pix, &env->s_dst_pix);
}
