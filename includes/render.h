/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:02 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:23:03 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "map.h"

# define TOUCH_X_AXIS	0
# define TOUCH_Y_AXIS	1

typedef struct s_pixel
{
	int	x;
	int	y;
	int	colour;
}				t_pixel;

typedef struct s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct s_env
{
	t_image	*dst_img;
	t_image	*tex_ceiling;
	t_image	*tex_floor;
	t_vec	s_ray_dir_l;
	t_vec	s_ray_dir_r;
	t_pixel	s_src_pix;
	t_pixel	s_dst_pix;
	t_vec	s_step;
	t_vec	s_coord;
	t_coord	s_grid_coord;
}				t_env;

typedef struct s_draw
{
	t_image	*dst_img;
	t_pixel	s_dst_pix;
	int		draw_start;
	int		draw_end;
	int		line_height;
}				t_draw;

typedef struct s_dist
{
	double	x;
	double	y;
}				t_dist;

typedef struct s_step
{
	int	x;
	int	y;
}				t_step;

typedef struct s_raycast
{
	t_vec	s_ray_dir;
	double	camera_x;
	t_coord	s_map_tmp;
	t_dist	s_side_dist;
	t_dist	s_delta_dist;
	t_step	s_step;
	double	wall_dist;
	bool	side_touched;
}				t_raycast;

/* draw environment */
void	ft_draw_text_env(t_game *game, t_player *pl);

/* draw wall */
void	ft_draw_wall(t_game *game, t_draw *draw);

/* drawing */
void	ft_draw(t_game *game, int x);

/* render */
int		ft_render(t_game *game);

#endif
