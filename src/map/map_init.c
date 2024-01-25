#include "map.h"
#include "utils.h"

uint8_t	ft_init_map(char *file, t_map *map);

uint8_t	ft_init_map(char *file, t_map *map)
{
	return (ft_throw_map_exception(ft_parse_map(file, map)));
//		return (1);
//	map->grid = ft_calloc(25, sizeof(int32_t));
//	if (map->grid == NULL)
//		return (1);
//	int32_t grid[25] = 	{1, 1, 1, 1, 1,
//						1, 0, 0, 0, 1,
//						1, 0, 0, 0, 1,
//						1, 0, 0, 0, 1,
//						1, 1, 1, 1, 1};
//	int32_t i = 0;
//	while (i < 25)
//	{
//		map->grid[i] = (t_element) grid[i];
//		++i;
//	}
//	return (0);
}
