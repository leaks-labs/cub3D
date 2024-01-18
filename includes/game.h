#ifndef GAME_H
# define GAME_H

# include <math.h>
# include "render.h"

# define ROTATION_VELOCITY	0.174532925199433 // (10 degrees * M_PI / 180)
# define MOVEMENT_VELOCITY	0.05
# define VER_VIEW_VELOCITY	60
# define FOV_FACTOR			0.65 // tan(66.0 degrees / 2.0 * M_PI / 180.0)

# define EMPTY_COLOR_MAP	0xffffe3
# define WALL_COLOR_MAP		0x464a4e

typedef struct s_game
{
	t_map		*map;
	t_graphx	*graphx;
	t_raycast	s_raycast;
	int			screen_center;
	double		size_factor;
	bool		show_minimap;
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
void	ft_move_back_forth(t_game *game, int key_code);
void	ft_move_left_right(t_game *game, int key_code);

/* game rotation */
void	ft_rotate(t_game *game, double factor);
void	ft_rotate_left_right(t_game *game, int key_code);
void	ft_look_up_down(t_game *game, int key_code);
void	ft_rescale_ver_view(int *screen_center, int window_height);

/* game event */
void	ft_escape(t_game *game);
void	ft_size_factor(t_game *game, int key_code);
void	ft_minimap_zoom(t_game *game, int key_code);

#endif
