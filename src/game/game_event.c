#include <stdlib.h>
#include "game.h"

void	ft_escape(t_game *game);
void	ft_size_factor(t_game *game, int key_code);
void	ft_minimap_zoom(t_game *game, int key_code);

void	ft_escape(t_game *game)
{
	ft_on_destroy(game);
}

void	ft_size_factor(t_game *game, int key_code)
{
	if (key_code == KEY_H)
		game->size_factor += 0.1;
	else if (key_code == KEY_L)
		game->size_factor -= 0.1;
	if (game->size_factor < 0.5)
		game->size_factor = 0.5;
	else if (game->size_factor > 2)
		game->size_factor = 2;
}

void	ft_minimap_zoom(t_game *game, int key_code)
{
	if (game->show_minimap == false)
		return ;
	if (key_code == KEY_I)
		game->map->s_mini_map.units += 10;
	else if (key_code == KEY_O)
		game->map->s_mini_map.units -= 10;
	if (game->map->s_mini_map.units < 10)
		game->map->s_mini_map.units = 10;
	else if (game->map->s_mini_map.units > 200)
		game->map->s_mini_map.units = 200;
	game->map->s_mini_map.steps = 1.0 / game->map->s_mini_map.units;
}
