#include "libx.h"
#include "game.h"

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx);
static void		*ft_mlx_init(void **mlx_ptr);
static void		*ft_mlx_new_window(void *mlx_ptr, void **mlx_win);
static void		*ft_mlx_new_image(void *mlx_ptr, void **mlx_img);
static void		*ft_mlx_new_mini_map_image(void *mlx_ptr, void **mlx_img);
static void		ft_set_images_metadata(t_game *game, t_graphx *graphx);
static void		ft_mlx_get_data_addr(t_image *image);
static void		ft_set_hooks(t_game *game, t_graphx *graphx);

#ifdef __APPLE__

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx)
{
	if (NULL == ft_mlx_init(&graphx->mlx_ptr))
		return (INIT_ERROR);
	if (NULL == ft_mlx_new_window(graphx->mlx_ptr, &graphx->s_window.mlx_win))
		return (CREATE_WINDOW_ERROR);
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, \
			&graphx->s_window.s_image.mlx_img))
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		return (CREATE_IMAGE_ERROR);
	}
	if (NULL == ft_mlx_new_mini_map_image(graphx->mlx_ptr, \
			&game->map->s_mini_map.s_image.mlx_img))
	{
		mlx_destroy_image(graphx->mlx_ptr, &graphx->s_window.s_image.mlx_img);
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		return (CREATE_IMAGE_ERROR);
	}
	ft_set_images_metadata(game, graphx);
	ft_set_hooks(game, graphx);
	return (NO_EXCEPTION);
}

#elif __linux__

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx)
{
	if (NULL == ft_mlx_init(&graphx->mlx_ptr))
		return (INIT_ERROR);
	if (NULL == ft_mlx_new_window(graphx->mlx_ptr, &graphx->s_window.mlx_win))
	{
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_WINDOW_ERROR);
	}
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, \
			&graphx->s_window.s_image.mlx_img))
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_IMAGE_ERROR);
	}
	if (NULL == ft_mlx_new_mini_map_image(graphx->mlx_ptr, \
			&game->map->s_mini_map.s_image.mlx_img))
	{
		mlx_destroy_image(graphx->mlx_ptr, &graphx->s_window.s_image.mlx_img);
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_IMAGE_ERROR);
	}
	ft_set_images_metadata(game, graphx);
	ft_set_hooks(game, graphx);
	return (NO_EXCEPTION);
}

#endif

static void	*ft_mlx_init(void **mlx_ptr)
{
	*mlx_ptr = mlx_init();
	return (*mlx_ptr);
}

static void	*ft_mlx_new_window(void *mlx_ptr, void **mlx_win)
{
	*mlx_win = mlx_new_window(mlx_ptr, \
							WINDOW_WIDTH, \
							WINDOW_HEIGHT, \
							(char *)WINDOW_NAME);
	return (*mlx_win);
}

static void	*ft_mlx_new_image(void *mlx_ptr, void **mlx_img)
{
	*mlx_img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (*mlx_img);
}

static void	*ft_mlx_new_mini_map_image(void *mlx_ptr, void **mlx_img)
{
	*mlx_img = mlx_new_image(mlx_ptr, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	return (*mlx_img);
}

static void		ft_set_images_metadata(t_game *game, t_graphx *graphx)
{
	graphx->s_window.s_image.width = WINDOW_WIDTH;
	graphx->s_window.s_image.height = WINDOW_HEIGHT;
	game->screen_center = graphx->s_window.s_image.height / 2;
	game->map->s_mini_map.s_image.width = MINI_MAP_WIDTH;
	game->map->s_mini_map.s_image.height = MINI_MAP_HEIGHT;
	ft_mlx_get_data_addr(&graphx->s_window.s_image);
	ft_mlx_get_data_addr(&game->map->s_mini_map.s_image);
}

static void	ft_mlx_get_data_addr(t_image *image)
{
	image->data = mlx_get_data_addr(image->mlx_img, \
									&image->bits_per_pixel, \
									&image->size_line, \
									&image->endian);
}

static void	ft_set_hooks(t_game *game, t_graphx *graphx)
{
	mlx_hook(graphx->s_window.mlx_win, ON_DESTROY, 0, &ft_on_destroy, game);
	mlx_hook(graphx->s_window.mlx_win, ON_KEYDOWN, (1L << 0), \
				&ft_key_handler, game);
	mlx_hook(graphx->s_window.mlx_win, ON_MOUSEMOVE, (1L << 6), \
				&ft_on_mouse_move, game);
	mlx_key_hook(graphx->s_window.mlx_win, &ft_key_up_handler, game);
	mlx_loop_hook(graphx->mlx_ptr, &ft_render, game);
}
