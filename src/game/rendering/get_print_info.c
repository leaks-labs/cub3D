#include "render.h"

void			ft_init_screen_info(t_screen *screen, t_slice *slice, int x);
t_orientation	ft_get_orientation(int bitwise);

void	ft_init_screen_info(t_screen *screen, t_slice *slice, int x)
{
	static const int	screen_center = WINDOW_HEIGHT / 2;

	screen->real_slice_height = slice->slice_height;
	screen->x = x;
	screen->y = screen_center - screen->real_slice_height / 2;
	screen->current_slice_offset = 0;
	if (screen->y < 0)
	{
		screen->current_slice_offset += -screen->y;
		screen->y = 0;
	}
	screen->max_slice_height = screen->real_slice_height;
	if (screen->max_slice_height > WINDOW_HEIGHT)
		screen->max_slice_height = WINDOW_HEIGHT;
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
	// to remove
	e_result = NORTH;
	// to remove
	return (e_result);
}
