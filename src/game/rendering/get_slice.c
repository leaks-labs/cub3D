#include "render.h"
#include "game.h"

void		ft_get_slice(t_game_data *gd, t_slice *slice, double angle);
static int	ft_get_slice_height(t_game_data *gd, t_slice *slice, double angle);

void	ft_get_slice(t_game_data *gd, t_slice *slice, double angle)
{
	slice->orientation_bitwise = UR_SW;
	if (ft_get_up_down(angle) == DOWN)
		slice->orientation_bitwise <<= 2;
	if (ft_get_left_right(angle) == LEFT)
		slice->orientation_bitwise <<= 1;
	slice->slice_height = ft_get_slice_height(gd, slice, angle);
	slice->x_offset = (int)round(slice->x_offset) % UNITS;
	slice->y_offset = (int)round(slice->y_offset) % UNITS;
}

static int	ft_get_slice_height(t_game_data *gd, t_slice *slice, double angle)
{
	double	len;

	len = ft_get_ray_len(gd, slice, angle);
	if (len < 1)
		len = 1;
	return ((int)round(UNITS * PLAYER_DISTANCE / len));
}
