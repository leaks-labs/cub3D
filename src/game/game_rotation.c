#include "game.h"

#include <stdio.h> /* to remove */

void	ft_rotate_to_left(t_game_data *game_data);
void	ft_rotate_to_right(t_game_data *game_data);
void	ft_rescale_angle(double *angle);

void	ft_rotate_to_left(t_game_data *game_data)
{
	printf("Key : <-\n");
	game_data->map->player.axis.z += ROTATION_VELOCITY;
	ft_rescale_angle(&game_data->map->player.axis.z);
	ft_render(game_data);
}

void	ft_rotate_to_right(t_game_data *game_data)
{
	printf("Key : ->\n");
	game_data->map->player.axis.z -= ROTATION_VELOCITY;
	ft_rescale_angle(&game_data->map->player.axis.z);
	ft_render(game_data);
}

void	ft_rescale_angle(double *angle)
{
	if (*angle >= RAD_MAX)
		*angle -= RAD_MAX;
	else if (*angle < 0)
		*angle += RAD_MAX;
}
