/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_key_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:31 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:24:32 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include "game.h"

int			ft_key_down_handler(int32_t key_code, t_game *game);
int			ft_key_up_handler(int32_t key_code, t_game *game);
static bool	ft_match_and_switch(int32_t *bit_switch, int key_code, bool on_off);
static void	ft_switch_mouse_mode(t_game *game);

int	ft_key_down_handler(int32_t key_code, t_game *game)
{
	ft_match_and_switch(&game->bit_switch, key_code, true);
	return (0);
}

int	ft_key_up_handler(int32_t key_code, t_game *game)
{
	if (ft_match_and_switch(&game->bit_switch, key_code, false) == true)
		return (0);
	else if (key_code == KEY_ESC)
		ft_escape(game);
	else if (key_code == KEY_P)
		game->show_minimap ^= 1;
	else if (key_code == KEY_M)
		ft_switch_mouse_mode(game);
	return (0);
}

static bool	ft_match_and_switch(int32_t *bit_switch, int key_code, bool on_off)
{
	static const t_dic_keys	s_dic_keys[N_BIT_KEY] = {\
		{KEY_W, BIT_KEY_W}, {KEY_S, BIT_KEY_S}, \
		{KEY_D, BIT_KEY_D}, {KEY_A, BIT_KEY_A}, \
		{KEY_ARROW_LEFT, BIT_KEY_ARROW_LEFT}, \
		{KEY_ARROW_RIGHT, BIT_KEY_ARROW_RIGHT}, \
		{KEY_ARROW_DOWN, BIT_KEY_ARROW_DOWN}, \
		{KEY_ARROW_UP, BIT_KEY_ARROW_UP}, \
		{KEY_I, BIT_KEY_I}, {KEY_O, BIT_KEY_O}};
	size_t					i;

	i = 0;
	while (i < N_BIT_KEY)
	{
		if (key_code == s_dic_keys[i].keycode)
		{
			if (on_off == true)
				*bit_switch |= s_dic_keys[i].bitwise;
			else
				*bit_switch &= ~(s_dic_keys[i].bitwise);
			return (true);
		}
		++i;
	}
	return (false);
}

#ifdef __APPLE__

static void	ft_switch_mouse_mode(t_game *game)
{
	if (game->s_mouse.mouse_tracked == false)
	{
		mlx_mouse_hide();
		mlx_mouse_move(game->graphx->s_window.mlx_win, \
						game->graphx->s_window.s_image.width / 2, \
						game->graphx->s_window.s_image.height / 2);
	}
	else
		mlx_mouse_show();
	game->s_mouse.mouse_tracked ^= 1;
}

#elif __linux__

static void	ft_switch_mouse_mode(t_game *game)
{
	if (game->s_mouse.mouse_tracked == false)
	{
		mlx_mouse_hide(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win);
		mlx_mouse_move(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win, \
						game->graphx->s_window.s_image.width / 2, \
						game->graphx->s_window.s_image.height / 2);
	}
	else
		mlx_mouse_show(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win);
	game->s_mouse.mouse_tracked ^= 1;
}

#endif
