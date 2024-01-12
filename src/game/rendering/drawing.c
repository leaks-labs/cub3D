#include "render.h"
#include "game.h"

void		ft_draw_slice(t_game_data *gd, t_slice *slice, int x_screen_offset);
static void	ft_draw_ceiling(t_game_data *gd, t_screen *screen, t_pixel *pixel);
static void	ft_draw_wall(t_game_data *gd, t_slice *slice, t_screen *screen, \
							t_pixel *pixel_dest);
static void	ft_draw_floor(t_game_data *gd, t_screen *screen, t_pixel *pixel);
static void	ft_draw_env_slice(t_image *img, t_pixel *pixel, int max_y);

void	ft_draw_slice(t_game_data *gd, t_slice *slice, int x_screen_offset)
{
	t_screen	s_screen;
	t_pixel		s_pixel_dest;

	ft_init_screen_info(&s_screen, slice, x_screen_offset, \
						gd->map->player.view.ver_view);
	s_pixel_dest.x = s_screen.x;
	s_pixel_dest.y = 0;
	ft_draw_ceiling(gd, &s_screen, &s_pixel_dest);
	ft_draw_wall(gd, slice, &s_screen, &s_pixel_dest);
	ft_draw_floor(gd, &s_screen, &s_pixel_dest);
}

static void	ft_draw_ceiling(t_game_data *gd, t_screen *screen, t_pixel *pixel)
{
	if (screen->min_wall_y > 0)
	{
		pixel->colour = gd->map->texture[CEILING].rgb[0];
		ft_draw_env_slice(&gd->graphx->window.image, pixel, screen->min_wall_y);
	}
}

static void	ft_draw_wall(t_game_data *gd, t_slice *slice, t_screen *screen, \
							t_pixel *pixel_dest)
{
	t_pixel			s_pixel_src;
	t_element		e_bloc_type;
	t_orientation	e_orientation;

	if ((slice->orientation_bitwise & TOUCH_H) > 0)
	{
		s_pixel_src.x = (int)slice->x_offset;
		e_bloc_type = slice->e_hor;
	}
	else
	{
		s_pixel_src.x = (int)slice->y_offset;
		e_bloc_type = slice->e_ver;
	}
	e_orientation = ft_get_orientation(slice->orientation_bitwise);
	pixel_dest->y = screen->min_wall_y;
	while (pixel_dest->y < screen->max_wall_y)
	{
		s_pixel_src.y = (int)(screen->current_wall_offset \
						* UNITS / screen->real_wall_height + 0.5);
		ft_pixel_cpy(&gd->map->texture[e_bloc_type].image[e_orientation], \
						&gd->graphx->window.image, &s_pixel_src, pixel_dest);
		screen->current_wall_offset++;
		pixel_dest->y++;
	}
}

static void	ft_draw_floor(t_game_data *gd, t_screen *screen, t_pixel *pixel)
{
	(void)screen;
	if (pixel->y < WINDOW_HEIGHT)
	{
		pixel->colour = gd->map->texture[FLOOR].rgb[0];
		ft_draw_env_slice(&gd->graphx->window.image, pixel, WINDOW_HEIGHT);
	}
}

static void	ft_draw_env_slice(t_image *img, t_pixel *pixel, int max_y)
{
	while (pixel->y < max_y)
	{
		ft_pixel_put(img, pixel);
		pixel->y++;
	}
}