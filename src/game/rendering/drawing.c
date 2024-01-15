#include "render.h"
#include "game.h"

void					ft_draw(t_game *game, int x);
static void				ft_draw_init(t_game *game, t_draw *draw, int x);
static void				ft_draw_ceiling(t_draw *draw, t_map *map);
static void				ft_draw_floor(t_draw *draw, t_map *map);

void	ft_draw(t_game *game, int x)
{
	t_draw	s_draw;

	ft_draw_init(game, &s_draw, x);
	ft_draw_ceiling(&s_draw, game->map);
	ft_draw_wall(game, &s_draw);
	ft_draw_floor(&s_draw, game->map);
}

static void	ft_draw_init(t_game *game, t_draw *draw, int x)
{
	draw->line_height = (int)(WINDOW_HEIGHT / game->s_raycast.wall_dist);
	draw->draw_start = game->screen_center - draw->line_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = game->screen_center + draw->line_height / 2;
	if (draw->draw_end >= WINDOW_HEIGHT)
		draw->draw_end = WINDOW_HEIGHT - 1;
	draw->s_dst_pix.x = x;
	draw->s_dst_pix.y = 0;
	draw->dst_img = &game->graphx->s_window.s_image;
}

static void	ft_draw_ceiling(t_draw *draw, t_map *map)
{
	if (draw->draw_start < 0)
		return ;
	draw->s_dst_pix.colour = map->texture[CEILING].rgb[0];
	while (draw->s_dst_pix.y < draw->draw_start)
	{
		ft_pixel_put(draw->dst_img, &draw->s_dst_pix);
		draw->s_dst_pix.y++;
	}
}

static void	ft_draw_floor(t_draw *draw, t_map *map)
{
	if (draw->draw_end >= WINDOW_HEIGHT - 1)
		return ;
	draw->s_dst_pix.colour = map->texture[FLOOR].rgb[0];
	while (draw->s_dst_pix.y < WINDOW_HEIGHT)
	{
		ft_pixel_put(draw->dst_img, &draw->s_dst_pix);
		draw->s_dst_pix.y++;
	}
}
