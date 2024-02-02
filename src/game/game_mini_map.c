/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:35 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:23:36 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		ft_draw_map(t_mini_map *mini_map, t_map *map);
static void	ft_draw_a_line(t_map *map, t_pixel *pix, t_vec *pos_tmp);
static void	ft_draw_player_pos(t_mini_map *mini_map, t_pixel *pix);
static void	ft_print_cursor_column(t_mini_map *mini_map, t_pixel *pix, \
									int diff, int y_start);
static void	ft_rotate_cursor(t_image *img, t_pixel *pix, double angle);

void	ft_draw_map(t_mini_map *mini_map, t_map *map)
{
	t_vec			s_pos_at_0;
	t_vec			s_pos_tmp;
	t_pixel			s_pix;

	s_pos_at_0.x = map->s_player.s_pos.x - \
					((mini_map->s_image.width / 2.0) / mini_map->units);
	s_pos_at_0.y = map->s_player.s_pos.y - \
					((mini_map->s_image.height / 2.0) / mini_map->units);
	s_pix.y = 0;
	s_pos_tmp.y = s_pos_at_0.y;
	while (s_pix.y < mini_map->s_image.height)
	{
		s_pix.x = 0;
		s_pos_tmp.x = s_pos_at_0.x;
		ft_draw_a_line(map, &s_pix, &s_pos_tmp);
		s_pix.y++;
		s_pos_tmp.y += mini_map->steps;
	}
	ft_draw_player_pos(mini_map, &s_pix);
}

static void	ft_draw_a_line(t_map *map, t_pixel *pix, t_vec *pos_tmp)
{
	t_mini_map	*mini_map;
	int			x_max;

	mini_map = &map->s_mini_map;
	while (pix->x < mini_map->s_image.width)
	{
		if (ft_isawall_coord(map, pos_tmp->x, pos_tmp->y) == true)
			pix->colour = mini_map->wall_color;
		else
			pix->colour = mini_map->empty_color;
		x_max = pix->x \
				+ (int)((floor(pos_tmp->x + 1.0) - pos_tmp->x) \
				* mini_map->units);
		if (x_max >= mini_map->s_image.width)
			x_max = mini_map->s_image.width - 1;
		while (pix->x <= x_max)
		{
			ft_pixel_put(&mini_map->s_image, pix);
			pix->x++;
			pos_tmp->x += mini_map->steps;
		}
	}
}

static void	ft_draw_player_pos(t_mini_map *mini_map, t_pixel *pix)
{
	const int	y_start = mini_map->s_image.height / 2;
	const int	max_x = mini_map->s_image.width / 2 + 11;
	int			diff;
	int			i;

	diff = 0;
	pix->x = mini_map->s_image.width / 2 - 8;
	pix->y = y_start;
	while (pix->x <= max_x)
	{
		i = 0;
		while (i++ < 3)
		{
			ft_print_cursor_column(mini_map, pix, diff, y_start);
			pix->x++;
		}
		diff++;
	}
}

static void	ft_print_cursor_column(t_mini_map *mini_map, t_pixel *pix, \
									int diff, int y_start)
{
	t_pixel	s_pix_rotated;

	s_pix_rotated.colour = CURSOR_COLOR_MAP;
	pix->y = y_start - diff;
	while (pix->y <= y_start + diff)
	{
		s_pix_rotated.x = pix->x;
		s_pix_rotated.y = pix->y;
		ft_rotate_cursor(&mini_map->s_image, &s_pix_rotated, mini_map->angle);
		ft_pixel_put(&mini_map->s_image, &s_pix_rotated);
		pix->y++;
	}
}

static void	ft_rotate_cursor(t_image *img, t_pixel *pix, double angle)
{
	const double	cos_fact = cos(angle);
	const double	sin_fact = sin(angle);
	double			old_x;

	pix->x -= img->width / 2;
	pix->y -= img->height / 2;
	old_x = pix->x;
	pix->x = (int)round(pix->x * cos_fact - pix->y * sin_fact);
	pix->y = (int)round(old_x * sin_fact + pix->y * cos_fact);
	pix->x += img->width / 2;
	pix->y += img->height / 2;
}
