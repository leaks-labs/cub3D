#include <stdlib.h>
#include "libx.h"
#include "game.h"

int	ft_key_handler(int32_t key_code, t_game_data *game_data);
int	ft_on_destroy(t_game_data *game_data);
int	ft_on_mouse_move(int x, int y, t_game_data *gd);
int	ft_key_up_handler(int32_t key_code, t_game_data *game_data);

int	ft_key_handler(int32_t key_code, t_game_data *game_data)
{
	static void (*const		f[N_KEY])(t_game_data *game_data, int key_code) = {\
			&ft_move_back_forth, &ft_move_back_forth, \
			&ft_move_left_right, &ft_move_left_right, \
			&ft_rotate_left_right, &ft_rotate_left_right, \
			&ft_look_up_down, &ft_look_up_down, \
			&ft_escape
	};
	static const t_keyboard	keyboard_key[N_KEY] = {\
			KEY_W, KEY_S, \
			KEY_A, KEY_D, \
			KEY_ARROW_LEFT, KEY_ARROW_RIGHT, \
			KEY_ARROW_DOWN, KEY_ARROW_UP, \
			KEY_ESC
	};
	size_t					i;

	i = 0;
	while (i < N_KEY)
	{
		if ((t_keyboard)key_code == keyboard_key[i])
			f[i](game_data, key_code);
		++i;
	}
	return (0);
}

int	ft_on_destroy(t_game_data *game_data)
{
	ft_destroy_game(game_data);
	exit(0);
}

#ifdef __APPLE__

int	ft_on_mouse_move(int x, int y, t_game_data *gd)
{
	double	dist_x;
	int		dist_y;

	if (gd->graphx->mouse_tracked == false)
		return (0);
	dist_x = (WINDOW_WIDTH / 2 - x) / 2.0;
	dist_y = (WINDOW_HEIGHT / 2 - y) * 2;
	gd->screen_center += dist_y;
	ft_rescale_ver_view(&gd->screen_center);
	ft_rotate(gd, -dist_x / 16);
	mlx_mouse_move(gd->graphx->window.mlx_win, \
					WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}

#elif __linux__

int	ft_on_mouse_move(int x, int y, t_game_data *gd)
{
	double	dist_x;
	int		dist_y;

	if (gd->graphx->mouse_tracked == false)
		return (0);
	dist_x = (WINDOW_WIDTH / 2 - x) / 2.0;
	dist_y = (WINDOW_HEIGHT / 2 - y) * 2;
	gd->screen_center += dist_y;
	ft_rescale_ver_view(&gd->screen_center);
	ft_rotate(gd, -dist_x / 16);
	mlx_mouse_move(gd->graphx->mlx_ptr, gd->graphx->window.mlx_win, \
					WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}

#endif

#ifdef __APPLE__

int	ft_key_up_handler(int32_t key_code, t_game_data *game_data)
{
	if (key_code == KEY_M)
	{
		if (game_data->graphx->mouse_tracked == false)
		{
			mlx_mouse_hide();
			mlx_mouse_move(game_data->graphx->window.mlx_win, \
							WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		}
		else
			mlx_mouse_show();
		game_data->graphx->mouse_tracked ^= 1;
	}
	return (0);
}

#elif __linux__

int	ft_key_up_handler(int32_t key_code, t_game_data *game_data)
{
	if (key_code == KEY_M)
	{
		if (game_data->graphx->mouse_tracked == false)
		{
			mlx_mouse_hide(game_data->graphx->mlx_ptr, \
							game_data->graphx->window.mlx_win);
			mlx_mouse_move(game_data->graphx->mlx_ptr, \
							game_data->graphx->window.mlx_win, \
							WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		}
		else
			mlx_mouse_show(game_data->graphx->mlx_ptr, \
							game_data->graphx->window.mlx_win);
		game_data->graphx->mouse_tracked ^= 1;
	}
	return (0);
}

#endif