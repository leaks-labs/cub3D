#include "game.h"
#include "map.h"
#include "libx.h"

uint8_t ft_run(t_map *map)
{
	t_game_data		game_data;
	t_graphx		graphx;

	ft_init_game_data(&game_data, &graphx, map);
	if (ft_throw_mlx_exception(ft_init_graphx(&game_data, &graphx)))
	{
		ft_destroy_map(game_data.map);
		return (1);
	}
	if (ft_render(&game_data)) /*should throw an exception */
	{
		ft_destroy_game(&game_data); /* Maybe it should be destroy_map() */
		return (1);
	}
	mlx_loop(graphx.mlx_ptr);
	return (0);
}
