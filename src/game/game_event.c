#include <stdlib.h>
#include "game.h"

void	ft_escape(t_game_data *game_data, int key_code);

void	ft_escape(t_game_data *game_data, int key_code)
{
	(void)key_code;
	ft_on_destroy(game_data);
}
