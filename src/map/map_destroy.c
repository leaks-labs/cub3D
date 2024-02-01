#include <stdlib.h>
#include "map.h"

void	ft_destroy_map(t_map *map);

void	ft_destroy_map(t_map *map)
{
	free(map->grid);
}
