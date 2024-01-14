#include "render.h"
#include "game.h"

void					ft_draw_wall(t_game_data *gd, t_draw *draw);
static t_orientation	ft_get_orientation(t_raycast *raycast);
static void				ft_texture_iter(t_draw *draw, t_game_data *gd, \
										t_image *src_img, double wall_x);

void	ft_draw_wall(t_game_data *gd, t_draw *draw)
{
	t_element		e_block_type;
	t_orientation	e_orientation;
	t_image			*src_img;
	double			wall_x;

	e_block_type = gd->map->grid[gd->raycast.s_map_tmp.x \
								+ gd->raycast.s_map_tmp.y * gd->map->width];
	e_orientation = ft_get_orientation(&gd->raycast);
	src_img = &gd->map->texture[e_block_type].image[e_orientation];
	if (gd->raycast.side_touched == TOUCH_X_AXIS)
		wall_x = gd->map->s_player.s_pos.y \
				+ gd->raycast.wall_dist * gd->raycast.s_ray_dir.y;
	else
		wall_x = gd->map->s_player.s_pos.x \
				+ gd->raycast.wall_dist * gd->raycast.s_ray_dir.x;
	wall_x -= floor(wall_x);
	ft_texture_iter(draw, gd, src_img, wall_x);
}

static t_orientation	ft_get_orientation(t_raycast *raycast)
{
	t_orientation	e_result;

	e_result = NORTH;
	if (raycast->side_touched == TOUCH_X_AXIS && raycast->s_ray_dir.x < 0)
		e_result = EAST;
	else if (raycast->side_touched == TOUCH_X_AXIS && raycast->s_ray_dir.x >= 0)
		e_result = WEST;
	else if (raycast->side_touched == TOUCH_Y_AXIS && raycast->s_ray_dir.y < 0)
		e_result = SOUTH;
	else if (raycast->side_touched == TOUCH_Y_AXIS && raycast->s_ray_dir.y >= 0)
		e_result = NORTH;
	return (e_result);
}

static void	ft_texture_iter(t_draw *draw, t_game_data *gd, t_image *src_img, \
							double wall_x)
{
	const double	step = 1.0 * TEX_HEIGHT / draw->line_height;
	t_pixel			s_tex;
	double			tex_pos;

	s_tex.x = (int)(wall_x * (double)(TEX_WIDTH));
	if (gd->raycast.side_touched == TOUCH_X_AXIS && gd->raycast.s_ray_dir.x > 0)
		s_tex.x = TEX_WIDTH - s_tex.x - 1;
	if (gd->raycast.side_touched == TOUCH_Y_AXIS && gd->raycast.s_ray_dir.y < 0)
		s_tex.x = TEX_WIDTH - s_tex.x - 1;
	tex_pos = (draw->draw_start - gd->screen_center + draw->line_height / 2) \
				* step;
	while (draw->s_dst_pix.y <= draw->draw_end)
	{
		// Cast the texture coordinate to integer,
		// and mask with (texHeight - 1) in case of overflow
		s_tex.y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		ft_pixel_cpy(src_img, draw->dst_img, &s_tex, &draw->s_dst_pix);
		draw->s_dst_pix.y++;
	}
}
