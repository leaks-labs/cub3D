#include "game.h"

void	ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map);

void	ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map)
{
	/* to remove */
	map->s_player.s_pos.x = 1.5;
	map->s_player.s_pos.y = 1.5;
	map->s_player.e_orientation = NORTH;
	/* to remove */

	graphx->mouse_tracked = false;
	game->show_minimap = false;
	map->s_player.s_dir.x = 0;
	map->s_player.s_dir.y = 0;
	map->s_player.s_plane.x = 0;
	map->s_player.s_plane.y = 0;
	game->size_factor = 1;
	if (map->s_player.e_orientation == EAST)
	{
		map->s_player.s_dir.x = 1;
		map->s_player.s_plane.y = FOV_FACTOR;
		map->s_mini_map.angle = RAD_EAST;
	}
	else if (map->s_player.e_orientation == WEST)
	{
		map->s_player.s_dir.x = -1;
		map->s_player.s_plane.y = -FOV_FACTOR;
		map->s_mini_map.angle = RAD_WEST;
	}
	if (map->s_player.e_orientation == NORTH)
	{
		map->s_player.s_dir.y = -1;
		map->s_player.s_plane.x = FOV_FACTOR;
		map->s_mini_map.angle = RAD_NORTH;
	}
	else if (map->s_player.e_orientation == SOUTH)
	{
		map->s_player.s_dir.y = 1;
		map->s_player.s_plane.x = -FOV_FACTOR;
		map->s_mini_map.angle = RAD_SOUTH;
	}
	map->s_mini_map.empty_color = EMPTY_COLOR_MAP;
	map->s_mini_map.wall_color = WALL_COLOR_MAP;
	map->s_mini_map.units = MINI_MAP_PIX_PER_CELL;
	map->s_mini_map.steps = 1.0 / map->s_mini_map.units;
	game->map = map;
	game->graphx = graphx;
}
