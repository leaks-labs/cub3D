#include <stdlib.h>
#include "libx.h"
#include "game.h"

int	ft_key_handler(int32_t key_code, t_game *game);
int	ft_on_destroy(t_game *game);
int	ft_on_mouse_move(int x, int y, t_game *game);
int	ft_key_up_handler(int32_t key_code, t_game *game);

int	ft_key_handler(int32_t key_code, t_game *game)
{
	static void (*const		f[N_KEY])(t_game *game, int key_code) = {\
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
			f[i](game, key_code);
		++i;
	}
	return (0);
}

int	ft_on_destroy(t_game *game)
{
	ft_destroy_game(game);
	exit(0);
}

#ifdef __APPLE__

int	ft_on_mouse_move(int x, int y, t_game *game)
{
	double	dist_x;
	int		dist_y;

	if (game->graphx->mouse_tracked == false)
		return (0);
	dist_x = (game->graphx->s_window.s_image.width / 2 - x) / 2.0;
	dist_y = (game->graphx->s_window.s_image.height / 2 - y) * 2;
	game->screen_center += dist_y;
	ft_rescale_ver_view(&game->screen_center, \
						game->graphx->s_window.s_image.height);
	ft_rotate(game, -dist_x / 16);
	mlx_mouse_move(game->graphx->s_window.mlx_win, \
					game->graphx->s_window.s_image.width / 2, \
					game->graphx->s_window.s_image.height / 2);
	return (0);
}

#elif __linux__

int	ft_on_mouse_move(int x, int y, t_game *game)
{
	double	dist_x;
	int		dist_y;

	if (game->graphx->mouse_tracked == false)
		return (0);
	dist_x = (game->graphx->s_window.s_image.width / 2 - x) / 2.0;
	dist_y = (game->graphx->s_window.s_image.height / 2 - y) * 2;
	game->screen_center += dist_y;
	ft_rescale_ver_view(&game->screen_center, \
						game->graphx->s_window.s_image.height);
	ft_rotate(game, -dist_x / 16);
	mlx_mouse_move(game->graphx->mlx_ptr, game->graphx->window.mlx_win, \
					game->graphx->s_window.s_image.width / 2, \
					game->graphx->s_window.s_image.height / 2);
	return (0);
}

#endif

#ifdef __APPLE__

int	ft_key_up_handler(int32_t key_code, t_game *game)
{
	if (key_code == KEY_M)
	{
		if (game->graphx->mouse_tracked == false)
		{
			mlx_mouse_hide();
			mlx_mouse_move(game->graphx->s_window.mlx_win, \
							game->graphx->s_window.s_image.width / 2, \
							game->graphx->s_window.s_image.height / 2);
		}
		else
			mlx_mouse_show();
		game->graphx->mouse_tracked ^= 1;
	}
	return (0);
}

#elif __linux__

int	ft_key_up_handler(int32_t key_code, t_game *game)
{
	if (key_code == KEY_M)
	{
		if (game->graphx->mouse_tracked == false)
		{
			mlx_mouse_hide(game->graphx->mlx_ptr, \
							game->graphx->window.mlx_win);
			mlx_mouse_move(game->graphx->mlx_ptr, \
							game->graphx->window.mlx_win, \
							game->graphx->s_window.s_image.width / 2, \
							game->graphx->s_window.s_image.height / 2);
		}
		else
			mlx_mouse_show(game->graphx->mlx_ptr, \
							game->graphx->window.mlx_win);
		game->graphx->mouse_tracked ^= 1;
	}
	return (0);
}

#endif