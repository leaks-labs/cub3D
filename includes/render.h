#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include "map.h"

# define UR_SW		1
# define UL_SE		2
# define DR_NW		4
# define DL_NE		8
# define TOUCH_Y	16
# define TOUCH_X	32

typedef enum e_render_exception
{
	/* No exception for now */
	NO_RENDER_EXCEPTION
}				t_render_exception;

typedef enum e_face_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}			t_face_dir;

typedef struct s_slice
{
	int			orientation_bitwise;
	double		x_offset;
	double		y_offset;
	t_element	e_hor;
	t_element	e_ver;
	int			slice_height;
}				t_slice;

typedef struct s_pixel
{
	int	x;
	int	y;
	int	colour;
}				t_pixel;

typedef struct s_screen
{
	int	x;
	int	y;
	int	max_slice_height;
	int	real_slice_height;
	int	current_slice_offset;
}				t_screen;

typedef struct s_dic_orient
{
	int				bitwise;
	t_orientation	e_orientation;
}				t_dic_orient;

/* drawing */
void				ft_draw_slice(t_game_data *gd, t_slice *slice, \
									int x_screen_offset);

/* get map info */
t_face_dir			ft_get_up_down(double angle);
t_face_dir			ft_get_left_right(double angle);
bool				ft_isinmap(t_pos *pos, t_map *map);
bool				ft_isawall_coord(t_map *map, t_pos *pos, \
										t_element *element);

/* get print info */
void				ft_init_screen_info(t_screen *screen, t_slice *slice, \
										int x);
t_orientation		ft_get_orientation(int bitwise);

/* get slice */
void				ft_get_slice(t_game_data *gd, t_slice *slice, double angle);

/* len to axis */
double				ft_get_len_to_h_stripe(t_game_data *gd, t_slice *slice, \
											double angle);
double				ft_get_len_to_v_stripe(t_game_data *gd, t_slice *slice, \
											double angle);

/* raycast */
double				ft_get_ray_len(t_game_data *gd, t_slice *slice, \
									double angle);

/* render */
t_render_exception	ft_render(t_game_data *game_data);

#endif
