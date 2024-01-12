#include "render.h"
#include "game.h"

t_render_exception	ft_render(t_game_data *game_data);

t_render_exception	ft_render(t_game_data *game_data)
{
	t_slice	s_slice;
	int		x_screen_offset;
	double	current_angle;

	// printf("\nbacklog :\n");
	// printf("x axis : %f\n", game_data->map->player.pos.x);
	// printf("y axis : %f\n", game_data->map->player.pos.y);
	// printf("rotation radiant : %f\n\n", game_data->map->player.axis.z);

	x_screen_offset = 0;
	current_angle = game_data->map->player.view.hor_view + (FOV / 2);
	ft_rescale_hor_view(&current_angle);
	while (x_screen_offset < WINDOW_WIDTH)
	{
		ft_get_slice(game_data, &s_slice, current_angle);
		ft_draw_slice(game_data, &s_slice, x_screen_offset);
		current_angle -= ANGLE_RAYS;
		ft_rescale_hor_view(&current_angle);
		++x_screen_offset;
	}
	ft_refresh(game_data);
	return (NO_RENDER_EXCEPTION);
}
