#include "game.h"

#include <stdio.h> /* to remove */

void	ft_rotate_to_left(t_game_data *game_data);
void	ft_rotate_to_right(t_game_data *game_data);

void	ft_rotate_to_left(t_game_data *game_data)
{
	printf("Key : <-\n");
	game_data->map->player.axis.z += ROTATION_VELOCITY;
	if (game_data->map->player.axis.z >= RAD_MAX)
		game_data->map->player.axis.z -= RAD_MAX;
	ft_render(game_data);
}

void	ft_rotate_to_right(t_game_data *game_data)
{
	printf("Key : ->\n");
	game_data->map->player.axis.z -= ROTATION_VELOCITY;
	if (game_data->map->player.axis.z < 0)
		game_data->map->player.axis.z += RAD_MAX;
	ft_render(game_data);
}
