#include <stdlib.h>
#include "libx.h"
#include "game.h"

int	ft_key_handler(int32_t key_code, t_game_data *game_data);
int	ft_on_destroy(t_game_data *game_data);
int	ft_on_mouse_move(int x, int y, t_game_data *game_data);
int	ft_key_down_handler(int32_t key_code, t_game_data *game_data);

int	ft_key_handler(int32_t key_code, t_game_data *game_data)
{
	static void (*const		f[N_KEY])(t_game_data *game_data) = {\
			&ft_go_forward, &ft_go_backward, \
			&ft_go_left, &ft_go_right, \
			&ft_rotate_to_left, &ft_rotate_to_right, \
			&ft_look_down, &ft_look_up, \
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
			f[i](game_data);
		++i;
	}
	return (0);
}

int	ft_on_destroy(t_game_data *game_data)
{
	ft_destroy_game(game_data);
	exit(0);
}

int	ft_on_mouse_move(int x, int y, t_game_data *game_data)
{
	int	dist_x;
	int	dist_y;

	if (game_data->graphx->mouse_tracked == false)
		return (0);
	dist_x = -((WINDOW_WIDTH / 2 - x) * 2);
	dist_y = ((WINDOW_HEIGHT / 2 - y) * 2);
	game_data->map->player.view.ver_view += dist_y;
	ft_rescale_ver_view(&game_data->map->player.view.ver_view);
	game_data->map->player.view.hor_view += ANGLE_RAYS * -dist_x;
	ft_rescale_hor_view(&game_data->map->player.view.hor_view);
	mlx_mouse_move(game_data->graphx->window.mlx_win, \
					WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	ft_render(game_data);
	return (0);
}

int	ft_key_down_handler(int32_t key_code, t_game_data *game_data)
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
