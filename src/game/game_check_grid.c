#include "game.h"

bool	ft_isawall_grid(t_map *map, int x, int y);
bool	ft_isawall_coord(t_map *map, double x, double y);

bool	ft_isawall_grid(t_map *map, int x, int y)
{
	return ((map->grid)[x + (y * map->width)] > 0);
}

bool	ft_isawall_coord(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= (double)map->width || y >= (double)map->height)
		return (true);
	return (ft_isawall_grid(map, (int)x, (int)y));
}
