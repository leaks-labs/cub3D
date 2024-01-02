#include "map.h"
#include "utils.h"

uint8_t ft_set_map(int argc, char *argv[], t_map *map)
{
	(void)argc;
	(void)argv;
	map->grid = ft_calloc(25, sizeof(int32_t));
	if (map->grid == NULL)
		return (1);
	int32_t grid[25] = 	{1, 1, 1, 1, 1,
						1, 0, 0, 0, 1,
						1, 0, 0, 0, 1,
						1, 0, 0, 0, 1,
						1, 1, 1, 1, 1};
	int32_t i = 0;
	while (i < 25)
	{
		map->grid[i] = grid[i];
		++i;
	}
	return (0);
}
