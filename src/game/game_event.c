#include <stdlib.h>
#include "game.h"

void	ft_escape(t_game *game);
void	ft_size_factor(t_game *game, int key_code);
void	ft_minimap_zoom(t_game *game, int key_code);
void	ft_rotate_mouse(t_game *game);

void	ft_escape(t_game *game)
{
	ft_on_destroy(game);
}

void	ft_size_factor(t_game *game, int key_code)
{
	if (key_code == KEY_H)
		game->size_factor += 0.1;
	else if (key_code == KEY_L)
		game->size_factor -= 0.1;
	if (game->size_factor < 0.5)
		game->size_factor = 0.5;
	else if (game->size_factor > 2)
		game->size_factor = 2;
}

void	ft_minimap_zoom(t_game *game, int key_code)
{
	(void)key_code;
	if (game->show_minimap == false)
		return ;
	if ((game->bit_switch & BIT_KEY_I) != 0 && (game->bit_switch & BIT_KEY_O) == 0)
		game->map->s_mini_map.units += M_MAP_ZOOM_SPEED;
	else if ((game->bit_switch & BIT_KEY_I) == 0 && (game->bit_switch & BIT_KEY_O) != 0)
		game->map->s_mini_map.units -= M_MAP_ZOOM_SPEED;
	else
		return ;
	if (game->map->s_mini_map.units < 10)
		game->map->s_mini_map.units = 10;
	else if (game->map->s_mini_map.units > 200)
		game->map->s_mini_map.units = 200;
	game->map->s_mini_map.steps = 1.0 / game->map->s_mini_map.units;
}

void	ft_rotate_mouse(t_game *game)
{
	const double	old_rot_left_right = game->s_mouse.rot_mouse_left_right;
	const int		old_rot_up_down = game->s_mouse.rot_mouse_up_down;

	game->screen_center += old_rot_up_down;
	ft_rescale_ver_view(&game->screen_center, \
						game->graphx->s_window.s_image.height);
	game->s_mouse.rot_mouse_up_down -= old_rot_up_down;
	ft_rotate(game, -old_rot_left_right / 8);
	game->map->s_mini_map.angle += (-old_rot_left_right / 8) \
									* ROTATION_VELOCITY;
	ft_rescale_angle(&game->map->s_mini_map.angle);
	game->s_mouse.rot_mouse_left_right -= old_rot_left_right;
}
