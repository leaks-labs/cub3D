/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:11 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:24:12 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include "game.h"

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx);
static void		*ft_mlx_init(void **mlx_ptr);
static void		*ft_mlx_new_window(void *mlx_ptr, void **mlx_win);
static void		ft_set_hooks(t_game *game, t_graphx *graphx);

#ifdef __APPLE__

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx)
{
	if (NULL == ft_mlx_init(&graphx->mlx_ptr))
		return (INIT_ERROR);
	if (NULL == ft_mlx_new_window(graphx->mlx_ptr, &graphx->s_window.mlx_win))
		return (CREATE_WINDOW_ERROR);
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, \
			&graphx->s_window.s_image.mlx_img))
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		return (CREATE_IMAGE_ERROR);
	}
	if (NULL == ft_mlx_new_mini_map_image(graphx->mlx_ptr, \
			&game->map->s_mini_map.s_image.mlx_img))
	{
		mlx_destroy_image(graphx->mlx_ptr, &graphx->s_window.s_image.mlx_img);
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		return (CREATE_IMAGE_ERROR);
	}
	ft_set_images_metadata(game, graphx);
	ft_set_hooks(game, graphx);
	return (NO_EXCEPTION);
}

#elif __linux__

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx)
{
	if (NULL == ft_mlx_init(&graphx->mlx_ptr))
		return (INIT_ERROR);
	if (NULL == ft_mlx_new_window(graphx->mlx_ptr, &graphx->s_window.mlx_win))
	{
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_WINDOW_ERROR);
	}
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, \
			&graphx->s_window.s_image.mlx_img))
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_IMAGE_ERROR);
	}
	if (NULL == ft_mlx_new_mini_map_image(graphx->mlx_ptr, \
			&game->map->s_mini_map.s_image.mlx_img))
	{
		mlx_destroy_image(graphx->mlx_ptr, &graphx->s_window.s_image.mlx_img);
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_IMAGE_ERROR);
	}
	ft_set_images_metadata(game, graphx);
	ft_set_hooks(game, graphx);
	return (NO_EXCEPTION);
}

#endif

static void	*ft_mlx_init(void **mlx_ptr)
{
	*mlx_ptr = mlx_init();
	return (*mlx_ptr);
}

static void	*ft_mlx_new_window(void *mlx_ptr, void **mlx_win)
{
	*mlx_win = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, \
								(char *)WINDOW_NAME);
	return (*mlx_win);
}

static void	ft_set_hooks(t_game *game, t_graphx *graphx)
{
	mlx_hook(graphx->s_window.mlx_win, ON_KEYDOWN, (1L << 0), \
				&ft_key_down_handler, game);
	mlx_hook(graphx->s_window.mlx_win, ON_KEYUP, (1L << 1), \
				&ft_key_up_handler, game);
	mlx_hook(graphx->s_window.mlx_win, ON_MOUSEMOVE, (1L << 6), \
				&ft_on_mouse_move, game);
	mlx_hook(graphx->s_window.mlx_win, ON_DESTROY, (1L << 17), \
				&ft_on_destroy, game);
	mlx_loop_hook(graphx->mlx_ptr, &ft_render, game);
}
