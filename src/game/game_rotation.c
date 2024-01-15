#include "game.h"

void	ft_rotate(t_game *game, double factor);
void	ft_rotate_left_right(t_game *game, int key_code);
void	ft_look_up_down(t_game *game, int key_code);
void	ft_rescale_ver_view(int *screen_center);

void	ft_rotate(t_game *game, double factor)
{
	const double	cos_factor = cos(ROTATION_VELOCITY * factor);
	const double	sin_factor = sin(ROTATION_VELOCITY * factor);
	const double	old_dir_x = game->map->s_player.s_dir.x;
	const double	old_plane_x = game->map->s_player.s_plane.x;

	game->map->s_player.s_dir.x = game->map->s_player.s_dir.x * cos_factor \
								- game->map->s_player.s_dir.y * sin_factor;
	game->map->s_player.s_dir.y = old_dir_x * sin_factor \
								+ game->map->s_player.s_dir.y * cos_factor;
	game->map->s_player.s_plane.x = game->map->s_player.s_plane.x * cos_factor \
									- game->map->s_player.s_plane.y * sin_factor;
	game->map->s_player.s_plane.y = old_plane_x * sin_factor \
									+ game->map->s_player.s_plane.y * cos_factor;
}

void	ft_rotate_left_right(t_game *game, int key_code)
{
	if (key_code == KEY_ARROW_LEFT)
		ft_rotate(game, -1);
	else if (key_code == KEY_ARROW_RIGHT)
		ft_rotate(game, 1);
}

void	ft_look_up_down(t_game *game, int key_code)
{
	if (key_code == KEY_ARROW_UP)
		game->screen_center += VER_VIEW_VELOCITY;
	if (key_code == KEY_ARROW_DOWN)
		game->screen_center -= VER_VIEW_VELOCITY;
	ft_rescale_ver_view(&game->screen_center);
}

void	ft_rescale_ver_view(int *screen_center)
{
	if (*screen_center < 10)
		*screen_center = 10;
	if (*screen_center >= WINDOW_HEIGHT - 10)
		*screen_center = WINDOW_HEIGHT - 10;
}
