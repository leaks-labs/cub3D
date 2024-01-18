#include <stdlib.h>
#include "libx.h"
#include "game.h"

int			ft_on_destroy(t_game *game);
int			ft_key_handler(int32_t key_code, t_game *game);
int			ft_on_mouse_move(int x, int y, t_game *game);
int			ft_key_up_handler(int32_t key_code, t_game *game);
static void	ft_switch_mouse_mode(t_game *game);

int	ft_on_destroy(t_game *game)
{
	ft_destroy_game(game);
	exit(0);
}

int	ft_key_handler(int32_t key_code, t_game *game)
{
	static const t_dic_keys	s_dic_keys[N_BIT_KEY] = {\
		{KEY_W, BIT_KEY_W}, {KEY_S, BIT_KEY_S}, \
		{KEY_D, BIT_KEY_D}, {KEY_A, BIT_KEY_A}, \
		{KEY_ARROW_LEFT, BIT_KEY_ARROW_LEFT}, \
		{KEY_ARROW_RIGHT, BIT_KEY_ARROW_RIGHT}, \
		{KEY_ARROW_DOWN, BIT_KEY_ARROW_DOWN}, \
		{KEY_ARROW_UP, BIT_KEY_ARROW_UP}, \
		{KEY_I, BIT_KEY_I}, {KEY_O, BIT_KEY_O}};
	size_t	i;

	i = 0;
	while (i < N_BIT_KEY)
	{
		if (key_code == s_dic_keys[i].keycode)
			game->bit_switch |= s_dic_keys[i].bitwise;
		++i;
	}
	return (0);
}

#ifdef __APPLE__

int	ft_on_mouse_move(int x, int y, t_game *game)
{
	if (game->s_mouse.mouse_tracked == false)
		return (0);
	game->s_mouse.rot_mouse_left_right += \
						(game->graphx->s_window.s_image.width / 2 - x) / 2.0;
	game->s_mouse.rot_mouse_up_down += \
						(game->graphx->s_window.s_image.height / 2 - y) * 3;
	mlx_mouse_move(game->graphx->s_window.mlx_win, \
					game->graphx->s_window.s_image.width / 2, \
					game->graphx->s_window.s_image.height / 2);
	return (0);
}

#elif __linux__

int	ft_on_mouse_move(int x, int y, t_game *game)
{
	if (game->graphx->mouse_tracked == false)
		return (0);
	game->s_switch.rot_mouse_left_right += \
						(game->graphx->s_window.s_image.width / 2 - x) / 2.0;
	game->s_switch.rot_mouse_up_down += \
						(game->graphx->s_window.s_image.height / 2 - y) * 2;
	mlx_mouse_move(game->graphx->mlx_ptr, game->graphx->s_window.mlx_win, \
					game->graphx->s_window.s_image.width / 2, \
					game->graphx->s_window.s_image.height / 2);
	return (0);
}

#endif

int	ft_key_up_handler(int32_t key_code, t_game *game)
{
	static const t_dic_keys	s_dic_keys[N_BIT_KEY] = {\
		{KEY_W, BIT_KEY_W}, {KEY_S, BIT_KEY_S}, \
		{KEY_D, BIT_KEY_D}, {KEY_A, BIT_KEY_A}, \
		{KEY_ARROW_LEFT, BIT_KEY_ARROW_LEFT}, \
		{KEY_ARROW_RIGHT, BIT_KEY_ARROW_RIGHT}, \
		{KEY_ARROW_DOWN, BIT_KEY_ARROW_DOWN}, \
		{KEY_ARROW_UP, BIT_KEY_ARROW_UP}, \
		{KEY_I, BIT_KEY_I}, {KEY_O, BIT_KEY_O}};
	size_t	i;

	i = 0;
	while (i < N_BIT_KEY)
	{
		if (key_code == s_dic_keys[i].keycode)
			game->bit_switch &= ~(s_dic_keys[i].bitwise);
		++i;
	}
	if (key_code == KEY_ESC)
		ft_escape(game);
	else if (key_code == KEY_P)
		game->show_minimap ^= 1;
	else if (key_code == KEY_M)
		ft_switch_mouse_mode(game);
	return (0);
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
	if (game->graphx->mouse_tracked == false)
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
	game->graphx->mouse_tracked ^= 1;
}

#endif