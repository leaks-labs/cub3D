#include "render.h"

void			ft_init_screen_info(t_screen *screen, t_slice *slice, int x);
t_orientation	ft_get_orientation(int bitwise);

void	ft_init_screen_info(t_screen *screen, t_slice *slice, int x)
{
	static const int	screen_center = WINDOW_HEIGHT / 2;

	screen->real_wall_height = slice->slice_height;
	screen->x = x;
	screen->min_wall_y = screen_center - screen->real_wall_height / 2;
	screen->max_wall_y = screen->min_wall_y + screen->real_wall_height;
	screen->current_wall_offset = 0;
	if (screen->min_wall_y < 0)
	{
		screen->current_wall_offset += -screen->min_wall_y;
		screen->min_wall_y = 0;
	}
	if (screen->max_wall_y > WINDOW_HEIGHT)
		screen->max_wall_y = WINDOW_HEIGHT;
}

t_orientation	ft_get_orientation(int bitwise)
{
	static const t_dic_orient	dic[8] = {{DR_NW | TOUCH_H, NORTH}, \
											{DL_NE | TOUCH_H, NORTH}, \
											{UR_SW | TOUCH_H, SOUTH}, \
											{UL_SE | TOUCH_H, SOUTH}, \
											{UR_SW | TOUCH_V, WEST}, \
											{DR_NW | TOUCH_V, WEST}, \
											{UL_SE | TOUCH_V, EAST}, \
											{DL_NE | TOUCH_V, EAST}};
	t_orientation				e_result;
	int							i;

	e_result = NORTH;
	i = 0;
	while (i < 8)
	{
		if (bitwise == dic[i].bitwise || bitwise == dic[++i].bitwise)
		{
			e_result = dic[i].e_orientation;
			break ;
		}
		++i;
	}
	return (e_result);
}
