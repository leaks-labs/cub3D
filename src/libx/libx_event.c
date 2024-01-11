#include <stdlib.h>
#include "libx.h"
#include "game.h"

int	ft_key_handler(int32_t key_code, t_game_data *game_data);
int	ft_on_destroy(t_game_data *game_data);

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
