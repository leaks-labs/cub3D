/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:26 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 18:15:20 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_destroy_game(t_game *game);

void	ft_destroy_game(t_game *game)
{
	ft_destroy_map(game->map);
	ft_destroy_texture(game->graphx->mlx_ptr, game->map->texture, \
						N_ORIENTATION, N_ELEMENT);
	ft_destroy_graphx(game);
}
