#ifndef GAME_H
# define GAME_H

# include <math.h>
# include <stdint.h>

# define ROTATION_SPEED	0.0873 /* 5 degrees */
# define MOVEMENT_SPEED	5
# define N_VECTOR		22 /* 2 rad div 5 degrees */

typedef struct s_map 	t_map;
typedef struct s_graphx	t_graphx;

typedef enum e_render_exception
{
	/* No exception for now */
	NO_RENDER_EXCEPTION
}				t_render_exception;

typedef struct	s_pos
{
	double	x;
	double	y;
	double	radian;
}				t_pos;

typedef struct	s_vector
{
	t_pos		pos;
	uint32_t	len;
}				t_vector;

typedef struct	s_player
{
	t_pos		pos;
	t_vector	vector[N_VECTOR];
}				t_player;

typedef struct	s_game_data
{
	t_map		*map;
	t_graphx	*graphx;
	t_player	player; /* Could be an array if multiplayer */
}				t_game_data;

uint8_t	ft_run(t_map *map);
t_render_exception ft_render(t_game_data *game_data);
/* Init and destroy */
void	ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map);
void	ft_destroy_game(t_game_data *game_data);
/* Throw error */

/* Game movement */
void	ft_go_forward(t_game_data *game_data);
void	ft_go_backward(t_game_data *game_data);
void	ft_go_left(t_game_data *game_data);
void	ft_go_right(t_game_data *game_data);

/* Game rotation */
void	ft_rotate_to_left(t_game_data *game_data);
void	ft_rotate_to_right(t_game_data *game_data);

/* Game event */
void	ft_escape(t_game_data *game_data);

#endif