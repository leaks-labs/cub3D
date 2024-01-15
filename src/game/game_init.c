#include "game.h"

void	ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map);

void	ft_init_game_data(t_game *game, t_graphx *graphx, t_map *map)
{
	/* to remove */
	map->s_player.s_pos.x = 1.5;
	map->s_player.s_pos.y = 1.5;
	map->s_player.e_orientation = NORTH;
	/* to remove */

	map->s_player.s_dir.x = 0;
	map->s_player.s_dir.y = 0;
	map->s_player.s_plane.x = 0;
	map->s_player.s_plane.y = 0;
	if (map->s_player.e_orientation == EAST)
	{
		map->s_player.s_dir.x = 1;
		map->s_player.s_plane.y = FOV_FACTOR;
	}
	else if (map->s_player.e_orientation == WEST)
	{
		map->s_player.s_dir.x = -1;
		map->s_player.s_plane.y = -FOV_FACTOR;
	}
	if (map->s_player.e_orientation == NORTH)
	{
		map->s_player.s_dir.y = -1;
		map->s_player.s_plane.x = FOV_FACTOR;
	}
	else if (map->s_player.e_orientation == SOUTH)
	{
		map->s_player.s_dir.y = 1;
		map->s_player.s_plane.x = -FOV_FACTOR;
	}
	game->map = map;
	game->graphx = graphx;
}
