/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:06 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:44:37 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include <stdlib.h>
#include "game.h"

void	ft_destroy_graphx(t_game *game);

#ifdef __APPLE__

void	ft_destroy_graphx(t_game *game)
{
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->graphx->s_window.s_image.mlx_img);
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->map->s_mini_map.s_image.mlx_img);
	mlx_destroy_window(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win);
	free(game->graphx->mlx_ptr);
}

#elif __linux__

void	ft_destroy_graphx(t_game *game)
{
	mlx_loop_end(game->graphx->mlx_ptr);
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->graphx->s_window.s_image.mlx_img);
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->map->s_mini_map.s_image.mlx_img);
	mlx_destroy_window(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win);
	mlx_destroy_display(game->graphx->mlx_ptr);
	free(game->graphx->mlx_ptr);
}

#endif
