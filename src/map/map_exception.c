#include <unistd.h>
#include "map.h"
#include "utils.h"

uint8_t	ft_throw_map_exception(t_map_exception e_map_exception);

uint8_t	ft_throw_map_exception(t_map_exception e_map_exception)
{
	const char	map_exception[N_MAP_EXCEPTION][MAP_LEN_ERROR] = {\
			MAP_EXTENSION_ERROR, \
			MAP_OPEN_ERROR, \
			MAP_REQUIREMENT_ERROR, \
			MAP_PATH_ERROR, \
			MAP_RGB_ERROR, \
			MAP_ELEMENT_ERROR
	};

	if (e_map_exception < N_MAP_EXCEPTION)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putendl_fd(map_exception[e_map_exception], STDERR_FILENO);
		return (1);
	}
	return (0);
}
