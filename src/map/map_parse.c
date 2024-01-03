#include "map.h"

t_map_exception ft_parse_map(char *file)
{
	if (1 == ft_check_extension(file))
		return (EXTENSION_ERROR);
	return (NO_MAP_EXCEPTION);
}
