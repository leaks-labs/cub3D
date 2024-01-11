#include <stdlib.h>
#include "game.h"

#include <stdio.h> /* to remove */

void	ft_escape(t_game_data *game_data);

void	ft_escape(t_game_data *game_data)
{
	printf("Key : ESC\n");
	// ft_destroy_game(game_data);
	// exit(0);
	ft_on_destroy(game_data);
}
