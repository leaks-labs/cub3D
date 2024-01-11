#ifndef GAME_H
# define GAME_H

# include <math.h>
# include "render.h"

# define RAD_MAX			6.283185307179586 /* (M_PI * 2) */
# define RECT_ANGLE			1.570796326794897 /* (90 * M_PI / 180) */

# define UNITS				64
# define PLAYER_VIEW		32 /* (UNITS / 2.0) */
# define FOV				1.047198 /* (60 * M_PI / 180) could be var */
# define ANGLE_RAYS			0.002094 /* ((60.0 / WINDOW_WIDTH) * M_PI / 180) */
# define PLAYER_DISTANCE	390	/* (WINDOW_WIDTH / 2) / tan(30 * M_PI / 180) */

# define ROTATION_VELOCITY	0.174532925199433 /* (10 * M_PI / 180) */
# define MOVEMENT_VELOCITY	10

# define EST_RAD			0
# define NORTH_RAD			1.570796
# define WEST_RAD			3.141593
# define SOUTH_RAD			4.712389

// typedef struct	s_vector
// { /* angle from origin */
// 	t_pos		*pos; /* obviously the player pos, could be the same ptr */
// 	double		orientation; /* radian */
// 	uint32_t	len;
// }				t_vector;

typedef struct s_game_data
{
	t_map		*map;
	t_graphx	*graphx;
	// t_player	player; /* Could be an array if multiplayer */
}				t_game_data;

/* runtime */
uint8_t	ft_run(t_map *map);

/* init and destroy */
void	ft_init_game_data(t_game_data *game_data, \
										t_graphx *graphx, t_map *map);
void	ft_destroy_game(t_game_data *game_data);
/* throw error */

/* game movement */
void	ft_go_forward(t_game_data *game_data);
void	ft_go_backward(t_game_data *game_data);
void	ft_go_left(t_game_data *game_data);
void	ft_go_right(t_game_data *game_data);

/* game rotation */
void	ft_rotate_to_left(t_game_data *game_data);
void	ft_rotate_to_right(t_game_data *game_data);
void	ft_rescale_angle(double *angle);

/* game event */
void	ft_escape(t_game_data *game_data);

#endif
