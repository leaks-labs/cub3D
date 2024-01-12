#include "render.h"
#include "game.h"

double			ft_get_len_to_h_stripe(t_game_data *gd, t_slice *slice, \
										double angle);
double			ft_get_len_to_v_stripe(t_game_data *gd, t_slice *slice, \
										double angle);
static t_pos	ft_get_first_h_stripe(t_game_data *gd, double angle);
static t_pos	ft_get_first_v_stripe(t_game_data *gd, double angle);
static double	ft_get_len_from_coord(t_pos *p, t_pos *d);

double	ft_get_len_to_h_stripe(t_game_data *gd, t_slice *slice, double angle)
{
	t_pos	tmp;
	double	x_steps;
	double	y_steps;

	tmp = ft_get_first_h_stripe(gd, angle);
	slice->x_offset = tmp.x;
	if (ft_isinmap(&tmp, gd->map) == false)
		return (-1);
	if (ft_isawall_coord(gd->map, &tmp, &slice->e_hor) == true)
		return (ft_get_len_from_coord(&gd->map->player.pos, &tmp));
	y_steps = UNITS;
	if (ft_get_up_down(angle) == UP)
		y_steps = -UNITS;
	x_steps = -y_steps / tan(angle);
	while (ft_isawall_coord(gd->map, &tmp, &slice->e_hor) == false)
	{
		tmp.x += x_steps;
		tmp.y += y_steps;
		slice->x_offset = tmp.x;
		if (ft_isinmap(&tmp, gd->map) == false)
			return (-1);
	}
	return (ft_get_len_from_coord(&gd->map->player.pos, &tmp));
}

double	ft_get_len_to_v_stripe(t_game_data *gd, t_slice *slice, double angle)
{
	t_pos	tmp;
	double	y_steps;
	double	x_steps;

	tmp = ft_get_first_v_stripe(gd, angle);
	slice->y_offset = tmp.y;
	if (ft_isinmap(&tmp, gd->map) == false)
		return (-1);
	if (ft_isawall_coord(gd->map, &tmp, &slice->e_ver) == true)
		return (ft_get_len_from_coord(&gd->map->player.pos, &tmp));
	x_steps = UNITS;
	if (ft_get_left_right(angle) == LEFT)
		x_steps = -UNITS;
	y_steps = -x_steps * tan(angle);
	while (ft_isawall_coord(gd->map, &tmp, &slice->e_ver) == false)
	{
		tmp.x += x_steps;
		tmp.y += y_steps;
		slice->y_offset = tmp.y;
		if (ft_isinmap(&tmp, gd->map) == false)
			return (-1);
	}
	return (ft_get_len_from_coord(&gd->map->player.pos, &tmp));
}

static t_pos	ft_get_first_h_stripe(t_game_data *gd, double angle)
{
	t_pos	tmp;

	if (ft_get_up_down(angle) == UP)
		tmp.y = floor(gd->map->player.pos.y / UNITS) * (UNITS) - 1;
	else
		tmp.y = floor(gd->map->player.pos.y / UNITS) * (UNITS) + UNITS;
	tmp.x = gd->map->player.pos.x \
			+ ((gd->map->player.pos.y - tmp.y) / tan(angle));
	return (tmp);
}

static t_pos	ft_get_first_v_stripe(t_game_data *gd, double angle)
{
	t_pos	tmp;

	if (ft_get_left_right(angle) == RIGHT)
		tmp.x = floor(gd->map->player.pos.x / UNITS) * (UNITS) + UNITS;
	else
		tmp.x = floor(gd->map->player.pos.x / UNITS) * (UNITS) - 1;
	tmp.y = gd->map->player.pos.y \
			+ ((gd->map->player.pos.x - tmp.x) * tan(angle));
	return (tmp);
}

static double	ft_get_len_from_coord(t_pos *p, t_pos *d)
{
	return (sqrt(pow(p->x - d->x, 2) + pow(p->y - d->y, 2)));
}
