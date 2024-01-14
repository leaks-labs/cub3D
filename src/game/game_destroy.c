#include "game.h"

void	ft_destroy_game(t_game_data *game_data);

void	ft_destroy_game(t_game_data *game_data)
{
	ft_destroy_map(game_data->map);
	ft_destroy_graphx(game_data->graphx);
	/* Then destroy the rest of the struct */
}
