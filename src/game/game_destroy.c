#include "game.h"

void	ft_destroy_game(t_game *game);

void	ft_destroy_game(t_game *game)
{
	ft_destroy_map(game->map);
	ft_destroy_graphx(game);
	// destroy the texture catalogue
	/* Then destroy the rest of the struct */
}
