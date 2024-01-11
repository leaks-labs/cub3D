#include "game.h"

#include <stdio.h> /* to remove */

void	ft_rotate_to_left(t_game_data *game_data);
void	ft_rotate_to_right(t_game_data *game_data);
void	ft_look_up(t_game_data *game_data);
void	ft_look_down(t_game_data *game_data);
void	ft_rescale_angle(double *angle);

void	ft_rotate_to_left(t_game_data *game_data)
{
	printf("Key : <-\n");
	game_data->map->player.view.hor_view += ROTATION_VELOCITY;
	ft_rescale_angle(&game_data->map->player.view.hor_view);
	ft_render(game_data);
}

void	ft_rotate_to_right(t_game_data *game_data)
{
	printf("Key : ->\n");
	game_data->map->player.view.hor_view -= ROTATION_VELOCITY;
	ft_rescale_angle(&game_data->map->player.view.hor_view);
	ft_render(game_data);
}

void	ft_look_up(t_game_data *game_data)
{
	printf("Key : haut\n");
	game_data->map->player.view.ver_view += VER_VIEW_VELOCITY;
	if (game_data->map->player.view.ver_view > WINDOW_HEIGHT - 10)
		game_data->map->player.view.ver_view = WINDOW_HEIGHT - 10;
	ft_render(game_data);
}

void	ft_look_down(t_game_data *game_data)
{
	printf("Key : bas\n");
	game_data->map->player.view.ver_view -= VER_VIEW_VELOCITY;
	if (game_data->map->player.view.ver_view < 10)
		game_data->map->player.view.ver_view = 10;
	ft_render(game_data);
}

void	ft_rescale_angle(double *angle)
{
	if (*angle >= RAD_MAX)
		*angle -= RAD_MAX;
	else if (*angle < 0)
		*angle += RAD_MAX;
}
