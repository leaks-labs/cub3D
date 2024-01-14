#include <stdlib.h>
#include "map.h"

void	ft_destroy_map(t_map *map);

void	ft_destroy_map(t_map *map)
{
	/* Should handle the rest of the game data struct,
	 * * but for now it's only grid */
	free(map->grid);
}
