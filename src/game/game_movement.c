#include "game.h"

#include <stdio.h> /* to remove */

void	ft_go_forward(t_game_data *game_data);
void	ft_go_backward(t_game_data *game_data);
void	ft_go_left(t_game_data *game_data);
void	ft_go_right(t_game_data *game_data);

void	ft_go_forward(t_game_data *game_data)
{
	double	x_dist;
	double	y_dist;

	printf("Key : W\n");
	/* check if collision with wall before incrementing */
	x_dist = cos(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	y_dist = sin(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	game_data->map->player.pos.x += x_dist;
	game_data->map->player.pos.y += y_dist;
	ft_render(game_data);
}

void	ft_go_backward(t_game_data *game_data)
{
	double	x_dist;
	double	y_dist;

	printf("Key : S\n");
	/* check if collision with wall before incrementing */
	x_dist = cos(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	y_dist = sin(-game_data->map->player.axis.z) * MOVEMENT_VELOCITY;
	game_data->map->player.pos.x -= x_dist;
	game_data->map->player.pos.y -= y_dist;
	ft_render(game_data);
}

void	ft_go_left(t_game_data *game_data)
{
	double	x_dist;
	double	y_dist;

	printf("Key : A\n");
	/* check if collision with wall before incrementing */
	x_dist = cos(-(game_data->map->player.axis.z + RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	y_dist = sin(-(game_data->map->player.axis.z + RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	game_data->map->player.pos.x += x_dist;
	game_data->map->player.pos.y += y_dist;
	ft_render(game_data);
}

void	ft_go_right(t_game_data *game_data)
{
	double	x_dist;
	double	y_dist;

	printf("Key : D\n");
	/* check if collision with wall before incrementing */
	x_dist = cos(-(game_data->map->player.axis.z - RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	y_dist = sin(-(game_data->map->player.axis.z - RECT_ANGLE)) \
				* MOVEMENT_VELOCITY;
	game_data->map->player.pos.x += x_dist;
	game_data->map->player.pos.y += y_dist;
	ft_render(game_data);
}
