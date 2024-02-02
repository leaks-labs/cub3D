/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:22:41 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:42:47 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <math.h>
# include "render.h"

# define ROTATION_VELOCITY	0.05
# define MOVEMENT_VELOCITY	0.05
# define VER_VIEW_VELOCITY	30
# define FOV_FACTOR			0.65 // tan(66.0 degrees / 2.0 * M_PI / 180.0)
# define M_MAP_ZOOM_SPEED	2

# define EMPTY_COLOR_MAP	0xffffe3
# define WALL_COLOR_MAP		0x464a4e
# define CURSOR_COLOR_MAP	0xff2800

# define RAD_WEST			0
# define RAD_NORTH			1.570796326794897 // (90 * M_PI / 180)
# define RAD_EAST			3.141592653589793 // (180 * M_PI / 180)
# define RAD_SOUTH			4.712388980384690 // (270 * M_PI / 180)
# define RAD_MAX			6.283185307179586 // (360 * M_PI / 180)

typedef struct s_mouse
{
	bool	mouse_tracked;
	double	rot_mouse_left_right;
	int		rot_mouse_up_down;
}				t_mouse;

typedef struct s_game
{
	t_map		*map;
	t_graphx	*graphx;
	t_raycast	s_raycast;
	int			screen_center;
	bool		show_minimap;
	int32_t		bit_switch;
	t_mouse		s_mouse;
}				t_game;

/* runtime */
uint8_t	ft_run(t_map *map);

/* check_grid */
bool	ft_isawall_grid(t_map *map, int x, int y);
bool	ft_isawall_coord(t_map *map, double x, double y);

/* init and destroy */
void	ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map);
void	ft_destroy_game(t_game *game);

/* mini map */
void	ft_draw_map(t_mini_map *mini_map, t_map *map);

/* game movement */
void	ft_move_back_forth(t_game *game);
void	ft_move_left_right(t_game *game);

/* game rotation */
void	ft_rotate(t_game *game, double factor);
void	ft_rotate_left_right(t_game *game);
void	ft_look_up_down(t_game *game);
void	ft_rescale_ver_view(int *screen_center, int window_height);
void	ft_rescale_angle(double *angle);

/* game event */
void	ft_escape(t_game *game);
void	ft_minimap_zoom(t_game *game);
void	ft_rotate_mouse(t_game *game);

#endif
