#include "game.h"

#include "stdio.h" // to remove

void	ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map);

void	ft_init_game_data(t_game_data *game_data, t_graphx *graphx, t_map *map)
{
	/* to remove */
	map->player.pos.x = 3;
	map->player.pos.y = 3;
	// map->player.pos.z = 0;
	// map->player.axis.x = 0;
	// map->player.axis.y = 0;
	map->player.axis.z = NORTH_RAD;
	map->width = 5;
	map->height = 5;
	/* to remove */

	map->player.pos.x = map->player.pos.x * UNITS + (UNITS / 2);
	map->player.pos.y = map->player.pos.y * UNITS + (UNITS / 2);

	game_data->map = map;
	game_data->graphx = graphx;
}
