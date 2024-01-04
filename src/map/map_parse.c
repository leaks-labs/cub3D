#include "map.h"
#include "utils.h"
#include <fcntl.h>

t_map_exception ft_parse_map(char *file)
{
	int32_t fd;

	if (1 == ft_check_extension(file))
		return (EXTENSION_ERROR);
	if (1 == ft_open_file(file, &fd))
		return (OPEN_ERROR);
	return (NO_MAP_EXCEPTION);
}

uint8_t ft_check_extension(const char *str)
{
	size_t i;

	i = ft_strlen(str);
	while (str[i] != '.' && i != 0)
		--i;
	return (ft_strcmp(&str[i], ".pub") != 0);
}

uint8_t ft_open_file(char *file, int32_t *fd)
{
	*fd = open(file, O_RDONLY);
	return (-1 == *fd);
}