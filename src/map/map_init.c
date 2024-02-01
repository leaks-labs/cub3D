#include "map.h"
#include "utils.h"

uint8_t	ft_init_map(char *file, t_map *map);

uint8_t	ft_init_map(char *file, t_map *map)
{
	return (ft_throw_map_exception(ft_parse_map(file, map)));
}
