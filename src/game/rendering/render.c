#include "render.h"
#include "game.h"

#include <math.h>
#include <stdio.h>

t_render_exception	ft_render(t_game_data *game_data);

t_render_exception	ft_render(t_game_data *game_data)
{
	t_slice	s_slice;
	int		x_screen_offset;
	double	current_angle;

	printf("\nbacklog : %.15f\n", (90 * M_PI / 180));
	// printf("\nbacklog :\n");
	// printf("x axis : %f\n", game_data->player.pos.x);
	// printf("y axis : %f\n", game_data->player.pos.y);
	// printf("rotation radiant : %f\n\n", game_data->player.axis.z);

	x_screen_offset = 0;
	current_angle = game_data->map->player.axis.z + (FOV / 2);
	while (x_screen_offset < WINDOW_WIDTH)
	{
		ft_get_slice(game_data, &s_slice, current_angle);
		ft_draw_slice(game_data, &s_slice, x_screen_offset);
		current_angle -= ANGLE_RAYS;
		++x_screen_offset;
	}
	ft_refresh(game_data);
	return (NO_RENDER_EXCEPTION);
}
