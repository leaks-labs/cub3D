#include "render.h"
#include "game.h"

t_face_dir	ft_get_up_down(double angle);
t_face_dir	ft_get_left_right(double angle);
bool		ft_isinmap(t_pos *pos, t_map *map);
bool		ft_isawall_coord(t_map *map, t_pos *pos, t_element *element);
static bool	ft_isawall_grid(t_map *map, int x, int y, t_element *element);

t_face_dir	ft_get_up_down(double angle)
{
	if (angle >= 0 && angle < WEST_RAD)
		return (UP);
	return (DOWN);
}

t_face_dir	ft_get_left_right(double angle)
{
	if ((angle <= NORTH_RAD && angle >= 0) || angle > SOUTH_RAD)
		return (RIGHT);
	return (LEFT);
}

bool	ft_isinmap(t_pos *pos, t_map *map)
{
	const double	x_max = map->width * UNITS;
	const double	y_max = map->height * UNITS;

	return (pos->x >= 0 && pos->x <= x_max && pos->y >= 0 && pos->y <= y_max);
}

bool	ft_isawall_coord(t_map *map, t_pos *pos, t_element *element)
{
	const int	x_grid = (int)(pos->x / UNITS);
	const int	y_grid = (int)(pos->y / UNITS);

	return (ft_isawall_grid(map, x_grid, y_grid, element));
}

static bool	ft_isawall_grid(t_map *map, int x, int y, t_element *element)
{
	*element = (map->grid)[x + (y * map->width)];
	return ((map->grid)[x + (y * map->width)] > 0);
}
