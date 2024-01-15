#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (1 == ft_init_map(argv[1], &map) || 1 == ft_run(&map));
}
