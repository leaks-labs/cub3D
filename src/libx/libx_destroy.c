#include <stdlib.h>
#include "libx.h"
#include "game.h"

void	ft_destroy_graphx(t_game *game);

#ifdef __APPLE__

void	ft_destroy_graphx(t_game *game)
{
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->graphx->s_window.s_image.mlx_img);
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->map->s_mini_map.s_image.mlx_img);
	mlx_destroy_window(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win);
	free(game->graphx->mlx_ptr); // necessary??
}

#elif __linux__

void	ft_destroy_graphx(t_game *game)
{
	mlx_loop_end(game->graphx->mlx_ptr);
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->graphx->s_window.s_image.mlx_img);
	mlx_destroy_image(game->graphx->mlx_ptr, \
						game->map->s_mini_map.s_image.mlx_img);
	mlx_destroy_window(game->graphx->mlx_ptr, \
						game->graphx->s_window.mlx_win);
	mlx_destroy_display(game->graphx->mlx_ptr);
	free(game->graphx->mlx_ptr);
}

#endif
