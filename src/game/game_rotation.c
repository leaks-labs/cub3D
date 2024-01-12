#include "game.h"

void	ft_rotate_to_left(t_game_data *game_data);
void	ft_rotate_to_right(t_game_data *game_data);
void	ft_look_up(t_game_data *game_data);
void	ft_look_down(t_game_data *game_data);

void	ft_rotate_to_left(t_game_data *game_data)
{
	game_data->map->player.view.hor_view += ROTATION_VELOCITY;
	ft_rescale_hor_view(&game_data->map->player.view.hor_view);
	ft_render(game_data);
}

void	ft_rotate_to_right(t_game_data *game_data)
{
	game_data->map->player.view.hor_view -= ROTATION_VELOCITY;
	ft_rescale_hor_view(&game_data->map->player.view.hor_view);
	ft_render(game_data);
}

void	ft_look_up(t_game_data *game_data)
{
	game_data->map->player.view.ver_view += VER_VIEW_VELOCITY;
	ft_rescale_ver_view(&game_data->map->player.view.ver_view);
	ft_render(game_data);
}

void	ft_look_down(t_game_data *game_data)
{
	game_data->map->player.view.ver_view -= VER_VIEW_VELOCITY;
	ft_rescale_ver_view(&game_data->map->player.view.ver_view);
	ft_render(game_data);
}
