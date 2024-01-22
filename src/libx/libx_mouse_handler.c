#include <stdlib.h>
#include "libx.h"
#include "game.h"

int	ft_on_destroy(t_game *game);
int	ft_on_mouse_move(int x, int y, t_game *game);

int	ft_on_destroy(t_game *game)
{
	ft_destroy_game(game);
	exit(0);
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
	if (game->s_mouse.mouse_tracked == false)
		return (0);
	game->s_mouse.rot_mouse_left_right += \
						(game->graphx->s_window.s_image.width / 2 - x) / 2.0;
	game->s_mouse.rot_mouse_up_down += \
						(game->graphx->s_window.s_image.height / 2 - y) * 2;
	mlx_mouse_move(game->graphx->mlx_ptr, game->graphx->s_window.mlx_win, \
					game->graphx->s_window.s_image.width / 2, \
					game->graphx->s_window.s_image.height / 2);
	return (0);
}

#endif
