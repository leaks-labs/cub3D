/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_mouse_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:38 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 18:15:14 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include <stdlib.h>
#include "game.h"

int	ft_on_destroy(t_game *game);
int	ft_on_mouse_move(int x, int y, t_game *game);

#ifdef __APPLE__

int	ft_on_destroy(t_game *game)
{
	ft_destroy_game(game);
	exit(0);
}

#elif __linux__

int	ft_on_destroy(t_game *game)
{
	mlx_loop_end(game->graphx->mlx_ptr);
	return (0);
}

#endif

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
