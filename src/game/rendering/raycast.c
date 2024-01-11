#include "render.h"
#include "game.h"

double			ft_get_ray_len(t_game_data *gd, t_slice *slice, double angle);
static double	ft_fisheye(double len, double ref_angle, double angle);

double	ft_get_ray_len(t_game_data *gd, t_slice *slice, double angle)
{
	double	actual_len;
	double	len_to_v_stripe;

	actual_len = ft_get_len_to_h_stripe(gd, slice, angle);
	len_to_v_stripe = ft_get_len_to_v_stripe(gd, slice, angle);
	if ((actual_len > len_to_v_stripe && len_to_v_stripe >= 0) \
			|| actual_len < 0)
	{
		actual_len = len_to_v_stripe;
		slice->orientation_bitwise |= TOUCH_V;
	}
	else
	{
		slice->orientation_bitwise |= TOUCH_H;
	}
	return (ft_fisheye(actual_len, gd->map->player.axis.z, angle));
}

static double	ft_fisheye(double len, double ref_angle, double angle)
{
	return ((len * cos(fabs(ref_angle - angle))));
}
