/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:46 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 18:15:18 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

uint8_t			ft_run(t_map *map);
t_mlx_exception	ft_open_texture(t_texture *texture, void *mlx_ptr);
void			ft_destroy_texture(void *mlx_ptr, t_texture *texture, \
									t_orientation e_orientation, \
									t_element e_element);

static int		ft_get_xpm(void *mlx_ptr, t_image *img, char *path);

uint8_t	ft_run(t_map *map)
{
	t_game			s_game;
	t_graphx		s_graphx;

	ft_init_game_data(&s_game, &s_graphx, map);
	if (ft_throw_mlx_exception(ft_init_graphx(&s_game, &s_graphx)))
	{
		ft_destroy_map(s_game.map);
		return (1);
	}
	if (ft_throw_mlx_exception(ft_open_texture(map->texture, s_graphx.mlx_ptr)))
	{
		ft_destroy_map(s_game.map);
		ft_destroy_graphx(&s_game);
		return (1);
	}
	mlx_loop(s_graphx.mlx_ptr);
	ft_destroy_game(&s_game);
	return (0);
}

t_mlx_exception	ft_open_texture(t_texture *texture, void *mlx_ptr)
{
	t_image			*tmp_img;
	char			*tmp_path;
	t_orientation	e_orientation;
	t_element		e_element;

	e_element = WALL;
	while (e_element < N_ELEMENT)
	{
		e_orientation = NORTH;
		while ((e_element < FLOOR || e_orientation == 0) \
				&& e_orientation < N_ORIENTATION)
		{
			tmp_img = &texture[e_element].image[e_orientation];
			tmp_path = texture[e_element].path[e_orientation];
			if (ft_get_xpm(mlx_ptr, tmp_img, tmp_path) != 0)
			{
				ft_destroy_texture(mlx_ptr, texture, e_orientation, e_element);
				return (CREATE_IMAGE_ERROR);
			}
			e_orientation++;
		}
		e_element++;
	}
	return (NO_EXCEPTION);
}

void	ft_destroy_texture(void *mlx_ptr, t_texture *texture, \
							t_orientation e_orientation, t_element e_element)
{
	t_image			*tmp_img;
	t_orientation	e_tmp_orientation;
	t_element		e_tmp_element;

	e_tmp_element = WALL;
	while (e_tmp_element <= e_element && e_tmp_element < N_ELEMENT)
	{
		e_tmp_orientation = NORTH;
		while (((e_tmp_element != e_element \
				&& e_tmp_orientation < N_ORIENTATION) \
				|| e_tmp_orientation < e_orientation) \
				&& (e_tmp_element < FLOOR || e_tmp_orientation == 0))
		{
			tmp_img = &texture[e_tmp_element].image[e_tmp_orientation];
			if (tmp_img->mlx_img != NULL)
				mlx_destroy_image(mlx_ptr, tmp_img->mlx_img);
			e_tmp_orientation++;
		}
		e_tmp_element++;
	}
}

static int	ft_get_xpm(void *mlx_ptr, t_image *img, char *path)
{
	if (path[0] != '\0')
	{
		img->mlx_img = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, \
											&img->height);
		if (img->mlx_img == NULL)
			return (-1);
		ft_mlx_get_data_addr(img);
	}
	else
	{
		img->mlx_img = NULL;
	}
	return (0);
}
