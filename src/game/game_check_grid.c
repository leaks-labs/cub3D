#include "game.h"

bool	ft_isawall_grid(t_map *map, int x, int y);
bool	ft_isawall_coord(t_map *map, double x, double y);

bool	ft_isawall_grid(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (true);
	return ((map->grid)[(size_t)x + (size_t)y * (size_t)map->width] > 0);
}

bool	ft_isawall_coord(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= (double)map->width || y >= (double)map->height)
		return (true);
	return (ft_isawall_grid(map, (int)x, (int)y));
}
