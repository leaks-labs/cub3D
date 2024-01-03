#include "game.h"

void ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map)
{
	game_data->player.pos.x = 0.000000;
	game_data->player.pos.y = 0.000000;
	game_data->player.pos.radian = 0.000000;
	game_data->map = map;
	game_data->graphx = graphx;
}
