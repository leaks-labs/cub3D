#include "render.h"
#include "game.h"

int				ft_render(t_game_data *gd);
static void		ft_raycast_init(t_player *pl, t_raycast *rc, int x);
static void		ft_raycast_side_dist_init(t_player *pl, t_raycast *rc);
static double	ft_get_ray_len(t_raycast *rc, t_map *map);

int	ft_render(t_game_data *gd)
{
	int	current_x;

	current_x = 0;
	while (current_x < WINDOW_WIDTH)
	{
		ft_raycast_init(&gd->map->s_player, &gd->raycast, current_x);
		gd->raycast.wall_dist = ft_get_ray_len(&gd->raycast, gd->map);
		ft_draw(gd, current_x);
		++current_x;
	}
	ft_refresh(gd);
	return (0);
}

static void	ft_raycast_init(t_player *pl, t_raycast *rc, int x)
{
	static const double	screen_width = (double)(WINDOW_WIDTH);

	//calculate ray position and direction
	rc->camera_x = 2 * x / screen_width - 1;
	rc->s_ray_dir.x = pl->s_dir.x + pl->s_plane.x * rc->camera_x;
	rc->s_ray_dir.y = pl->s_dir.y + pl->s_plane.y * rc->camera_x;

	// which box of the map we're in
	rc->s_map_tmp.x = (int)pl->s_pos.x;
	rc->s_map_tmp.y = (int)pl->s_pos.y;

	// length of ray from one x or y-side to next x or y-side
	// double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	// double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
	rc->s_delta_dist.x = fabs(1.0 / rc->s_ray_dir.x);
	rc->s_delta_dist.y = fabs(1.0 / rc->s_ray_dir.y);
	ft_raycast_side_dist_init(pl, rc);
}

static void	ft_raycast_side_dist_init(t_player *pl, t_raycast *rc)
{
	if (rc->s_ray_dir.x < 0)
	{
		rc->s_step.x = -1;
		rc->s_side_dist.x = (pl->s_pos.x - rc->s_map_tmp.x) \
							* rc->s_delta_dist.x;
	}
	else
	{
		rc->s_step.x = 1;
		rc->s_side_dist.x = (rc->s_map_tmp.x + 1.0 - pl->s_pos.x) \
							* rc->s_delta_dist.x;
	}
	if (rc->s_ray_dir.y < 0)
	{
		rc->s_step.y = -1;
		rc->s_side_dist.y = (pl->s_pos.y - rc->s_map_tmp.y) \
							* rc->s_delta_dist.y;
	}
	else
	{
		rc->s_step.y = 1;
		rc->s_side_dist.y = (rc->s_map_tmp.y + 1.0 - pl->s_pos.y) \
							* rc->s_delta_dist.y;
	}
}

static double	ft_get_ray_len(t_raycast *rc, t_map *map)
{
	bool	hit;

	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (rc->s_side_dist.x < rc->s_side_dist.y)
		{
			rc->s_side_dist.x += rc->s_delta_dist.x;
			rc->s_map_tmp.x += rc->s_step.x;
			rc->side_touched = TOUCH_X_AXIS;
		}
		else
		{
			rc->s_side_dist.y += rc->s_delta_dist.y;
			rc->s_map_tmp.y += rc->s_step.y;
			rc->side_touched = TOUCH_Y_AXIS;
		}
		// Check if ray has hit a wall
		if (map->grid[rc->s_map_tmp.x + rc->s_map_tmp.y * map->width] > 0)
			hit = 1;
	}
	// Calculate distance projected on camera direction
	// (Euclidean distance would give fisheye effect!)
	if (rc->side_touched == TOUCH_X_AXIS)
		return (rc->s_side_dist.x - rc->s_delta_dist.x);
	return (rc->s_side_dist.y - rc->s_delta_dist.y);
}
