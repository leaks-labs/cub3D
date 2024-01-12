#include "render.h"
#include "game.h"

void	ft_rescale_hor_view(double *angle);
void	ft_rescale_ver_view(int *ver_view);

void	ft_rescale_hor_view(double *angle)
{
	if (*angle >= RAD_MAX)
		*angle -= RAD_MAX;
	else if (*angle < 0)
		*angle += RAD_MAX;
}

void	ft_rescale_ver_view(int *ver_view)
{
	if (*ver_view < 10)
		*ver_view = 10;
	else if (*ver_view > WINDOW_HEIGHT - 10)
		*ver_view = WINDOW_HEIGHT - 10;
}
