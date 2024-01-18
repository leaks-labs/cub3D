#include "game.h"

void	ft_move_back_forth(t_game *game, int key_code);
void	ft_move_left_right(t_game *game, int key_code);

void	ft_move_back_forth(t_game *game, int key_code)
{
	double	new_x_real;
	double	new_y_real;
	int		new_x_grid;
	int		new_y_grid;
	int		dir;

	dir = 1;
	if (key_code == KEY_W)
		dir = 1;
	else if (key_code == KEY_S)
		dir = -1;
	new_x_real = game->map->s_player.s_pos.x \
					+ game->map->s_player.s_dir.x * MOVEMENT_VELOCITY * dir;
	new_y_real = game->map->s_player.s_pos.y \
					+ game->map->s_player.s_dir.y * MOVEMENT_VELOCITY * dir;
	new_x_grid = (int)new_x_real;
	new_y_grid = (int)new_y_real;
	if (!ft_isawall_grid(game->map, new_x_grid, \
						(int)game->map->s_player.s_pos.y))
		game->map->s_player.s_pos.x = new_x_real;
	if (!ft_isawall_grid(game->map, (int)game->map->s_player.s_pos.x, \
							new_y_grid))
		game->map->s_player.s_pos.y = new_y_real;
}

void	ft_move_left_right(t_game *game, int key_code)
{
	double	new_x_real;
	double	new_y_real;
	int		new_x_grid;
	int		new_y_grid;
	int		dir;

	dir = 1;
	if (key_code == KEY_A)
		dir = -1;
	else if (key_code == KEY_D)
		dir = 1;
	new_x_real = game->map->s_player.s_pos.x \
					+ game->map->s_player.s_plane.x * MOVEMENT_VELOCITY * dir;
	new_y_real = game->map->s_player.s_pos.y \
					+ game->map->s_player.s_plane.y * MOVEMENT_VELOCITY * dir;
	new_x_grid = (int)new_x_real;
	new_y_grid = (int)new_y_real;
	if (!ft_isawall_grid(game->map, new_x_grid, \
						(int)game->map->s_player.s_pos.y))
		game->map->s_player.s_pos.x = new_x_real;
	if (!ft_isawall_grid(game->map, (int)game->map->s_player.s_pos.x, \
							new_y_grid))
		game->map->s_player.s_pos.y = new_y_real;
}
