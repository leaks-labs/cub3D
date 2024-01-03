#include "game.h"

#include <stdio.h> /* to remove */

t_render_exception ft_render(t_game_data *game_data)
{
	printf("x axis : %f\n", game_data->player.pos.x);
	printf("y axis : %f\n", game_data->player.pos.y);
	printf("rotation radiant : %f\n", game_data->player.pos.radian);
	return (NO_RENDER_EXCEPTION);
}