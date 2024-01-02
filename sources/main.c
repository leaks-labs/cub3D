#include <stdlib.h>
#include "map.h"
#include "utils.h"
#include "game.h"

int main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (EXIT_FAILURE);
	}
	return (1 == ft_set_map(argc, argv, &map) || 1 == ft_run(&map));
}