#include "game.h"
#include <math.h>

#include <stdio.h> /* to remove */

void ft_rotate_to_left(t_game_data *game_data)
{

	printf("Key : <-\n");
	game_data->player.pos.radian += ROTATION_SPEED;
	if (game_data->player.pos.radian >= M_2_PI)
		game_data->player.pos.radian -= M_2_PI;
	ft_render(game_data);
}

void ft_rotate_to_right(t_game_data *game_data)
{
	printf("Key : ->\n");
	game_data->player.pos.radian -= ROTATION_SPEED;
	if (game_data->player.pos.radian <= 0)
		game_data->player.pos.radian += M_2_PI;
	ft_render(game_data);
}