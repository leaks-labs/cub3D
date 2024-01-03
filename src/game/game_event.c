#include "game.h"
#include <stdlib.h>

#include <stdio.h> /* to remove */

void ft_escape(t_game_data *game_data)
{
	printf("Key : ESC\n");
	ft_destroy_game(game_data);
	exit(1);
}