#ifndef GAME_H
# define GAME_H

# ifdef __linux__
#  include <stdint.h>
# endif

typedef struct s_map 	t_map;
typedef struct s_graphx	t_graphx;

typedef enum e_render_exception
{
	/* No exception for now */
	NO_RENDER_EXCEPTION
}				t_render_exception;

typedef struct	s_game_data
{
	t_map		*map;
	t_graphx	*graphx;
}				t_game_data;

uint8_t	ft_run(t_map *map);
t_render_exception ft_render(t_game_data *game_data);
/* Init and destroy */
void	ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map);
void	ft_destroy_game(t_game_data *game_data);
/* Throw error */

/* Game event */
void	ft_go_forward(t_game_data *game_data);
void	ft_go_backward(t_game_data *game_data);
void	ft_go_left(t_game_data *game_data);
void	ft_go_right(t_game_data *game_data);
void	ft_escape(t_game_data *game_data);

#endif