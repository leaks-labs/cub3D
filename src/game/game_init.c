#include "map.h"

void ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map)
{
	game_data->map->player.axis.z = 0.000000;

	game_data->map->player.pos.x = 0.000000;
	game_data->map->player.pos.y = 0.000000;
	game_data->map->player.pos.z = 0.000000;

	game_data->map = map;
	game_data->graphx = graphx;
}
