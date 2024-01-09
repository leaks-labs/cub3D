#include "map.h"
#include "libx.h"

#include <stdio.h> /* to remove */

void ft_go_forward(t_game_data *game_data)
{
	printf("Key : W\n");
	/* check if collision with wall before incrementing */
	game_data->map->player.pos.x += MOVEMENT_VELOCITY;
	ft_render(game_data);
}

void ft_go_backward(t_game_data *game_data)
{
	printf("Key : S\n");
	/* check if collision with wall before incrementing */
	game_data->map->player.pos.x -= MOVEMENT_VELOCITY;
	ft_render(game_data);
}

void ft_go_left(t_game_data *game_data)
{
	printf("Key : A\n");
	/* check if collision with wall before incrementing */
	game_data->map->player.pos.y -= MOVEMENT_VELOCITY;
	ft_render(game_data);
}

void ft_go_right(t_game_data *game_data)
{
	printf("Key : D\n");
	/* check if collision with wall before incrementing */
	game_data->map->player.pos.y += MOVEMENT_VELOCITY;
	ft_render(game_data);
}