#include "game.h"

#include <stdio.h> /* to remove */

void			ft_go_forward(t_game_data *game_data);
void			ft_go_backward(t_game_data *game_data);
void			ft_go_left(t_game_data *game_data);
void			ft_go_right(t_game_data *game_data);
static t_pos	ft_get_update_pos(t_map *map, t_pos *src, \
									double x_dist, double y_dist);

void	ft_go_forward(t_game_data *game_data)
{
	t_pos	start_pos;
	t_pos	new_pos;
	double	x_dist;
	double	y_dist;

	printf("Key : W\n");
	start_pos = game_data->map->player.pos;
	x_dist = cos(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	y_dist = sin(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	new_pos = ft_get_update_pos(game_data->map, &start_pos, x_dist, y_dist);
	game_data->map->player.pos = new_pos;
	ft_render(game_data);
}

void	ft_go_backward(t_game_data *game_data)
{
	t_pos	start_pos;
	t_pos	new_pos;
	double	x_dist;
	double	y_dist;

	printf("Key : S\n");
	start_pos = game_data->map->player.pos;
	x_dist = -cos(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	y_dist = -sin(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	new_pos = ft_get_update_pos(game_data->map, &start_pos, x_dist, y_dist);
	game_data->map->player.pos = new_pos;
	ft_render(game_data);
}

void	ft_go_left(t_game_data *game_data)
{
	t_pos	start_pos;
	t_pos	new_pos;
	double	x_dist;
	double	y_dist;

	printf("Key : A\n");
	start_pos = game_data->map->player.pos;
	x_dist = cos(-(game_data->map->player.axis.z + RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	y_dist = sin(-(game_data->map->player.axis.z + RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	new_pos = ft_get_update_pos(game_data->map, &start_pos, x_dist, y_dist);
	game_data->map->player.pos = new_pos;
	ft_render(game_data);
}

void	ft_go_right(t_game_data *game_data)
{
	t_pos	start_pos;
	t_pos	new_pos;
	double	x_dist;
	double	y_dist;

	printf("Key : D\n");
	start_pos = game_data->map->player.pos;
	x_dist = cos(-(game_data->map->player.axis.z - RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	y_dist = sin(-(game_data->map->player.axis.z - RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	new_pos = ft_get_update_pos(game_data->map, &start_pos, x_dist, y_dist);
	game_data->map->player.pos = new_pos;
	ft_render(game_data);
}

static t_pos	ft_get_update_pos(t_map *map, t_pos *src, \
									double x_dist, double y_dist)
{
	t_pos	pos;
	t_pos	tmp;

	pos = *src;
	tmp = *src;
	tmp.x += x_dist;
	if (ft_isawall_coord(map, &tmp, NULL) == false)
		pos = tmp;
	tmp.y += y_dist;
	if (ft_isawall_coord(map, &tmp, NULL) == false)
		pos = tmp;
	if ((int)src->x != (int)pos.x || (int)src->y != (int)pos.y)
		return (pos);
	tmp = *src;
	tmp.y += y_dist;
	if (ft_isawall_coord(map, &tmp, NULL) == false)
		pos = tmp;
	tmp.x += x_dist;
	if (ft_isawall_coord(map, &tmp, NULL) == false)
		pos = tmp;
	return (pos);
}
