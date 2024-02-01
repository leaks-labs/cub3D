#include "game.h"

void	ft_destroy_game(t_game *game);

void	ft_destroy_game(t_game *game)
{
	ft_destroy_map(game->map);
	ft_destroy_texture(game->graphx->mlx_ptr, game->map->texture, \
                            N_ORIENTATION, N_ELEMENT);
	ft_destroy_graphx(game);
}
