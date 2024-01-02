#include "game.h"
#include "libx.h"
#include <stdlib.h>

#include <stdio.h>

void ft_go_forward(t_game_data *game_data)
{
	printf("Key : W\n");
	ft_render(game_data);
}

void ft_go_backward(t_game_data *game_data)
{
	printf("Key : S\n");
	ft_render(game_data);
}

void ft_go_left(t_game_data *game_data)
{
	printf("Key : A\n");
	ft_render(game_data);
}

void ft_go_right(t_game_data *game_data)
{
	printf("Key : D\n");
	ft_render(game_data);
}

void ft_escape(t_game_data *game_data)
{
	printf("Key : ESC\n");
	ft_destroy_game(game_data);
	exit(1);
}