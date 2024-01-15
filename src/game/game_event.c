#include <stdlib.h>
#include "game.h"

void	ft_escape(t_game *game, int key_code);

void	ft_escape(t_game *game, int key_code)
{
	(void)key_code;
	ft_on_destroy(game);
}
