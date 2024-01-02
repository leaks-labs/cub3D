#include "game.h"

void ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map)
{
	game_data->map = map;
	game_data->graphx = graphx;
}
