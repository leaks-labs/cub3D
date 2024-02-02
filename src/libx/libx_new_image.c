/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_new_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:42 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:37:18 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include "game.h"

void	*ft_mlx_new_image(void *mlx_ptr, void **mlx_img);
void	*ft_mlx_new_mini_map_image(void *mlx_ptr, void **mlx_img);
void	ft_set_images_metadata(t_game *game, t_graphx *graphx);
void	ft_mlx_get_data_addr(t_image *image);

void	*ft_mlx_new_image(void *mlx_ptr, void **mlx_img)
{
	*mlx_img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (*mlx_img);
}

void	*ft_mlx_new_mini_map_image(void *mlx_ptr, void **mlx_img)
{
	*mlx_img = mlx_new_image(mlx_ptr, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	return (*mlx_img);
}

void	ft_set_images_metadata(t_game *game, t_graphx *graphx)
{
	graphx->s_window.s_image.width = WINDOW_WIDTH;
	graphx->s_window.s_image.height = WINDOW_HEIGHT;
	game->screen_center = graphx->s_window.s_image.height / 2;
	game->map->s_mini_map.s_image.width = MINI_MAP_WIDTH;
	game->map->s_mini_map.s_image.height = MINI_MAP_HEIGHT;
	ft_mlx_get_data_addr(&graphx->s_window.s_image);
	ft_mlx_get_data_addr(&game->map->s_mini_map.s_image);
}

void	ft_mlx_get_data_addr(t_image *image)
{
	image->data = mlx_get_data_addr(image->mlx_img, \
									&image->bits_per_pixel, \
									&image->size_line, \
									&image->endian);
}
