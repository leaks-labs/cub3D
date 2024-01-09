#include "map.h"

#include <stdio.h> /* to remove */

t_render_exception ft_render(t_game_data *game_data)
{
	printf("backlog :\n");
	printf("x axis : %f\n", game_data->map->player.pos.x);
	printf("y axis : %f\n", game_data->map->player.pos.y);
	printf("rotation radiant : %f\n", game_data->map->player.axis.z);
	return (NO_RENDER_EXCEPTION);
}