#include "libx.h"
#include "game.h"

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx);
static void		*ft_mlx_init(void **mlx_ptr);
static void		*ft_mlx_new_window(void *mlx_ptr, void **mlx_win);
static void		*ft_mlx_new_image(void *mlx_ptr, void **mlx_img);
static void		ft_mlx_get_data_addr(t_image *image);

#ifdef __APPLE__

t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx)
{
	if (NULL == ft_mlx_init(&graphx->mlx_ptr))
		return (INIT_ERROR);
	if (NULL == ft_mlx_new_window(graphx->mlx_ptr, &graphx->s_window.mlx_win))
		return (CREATE_WINDOW_ERROR);
	// need loop if add minimap
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, \
			&graphx->s_window.s_image.mlx_img))
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		return (CREATE_IMAGE_ERROR);
	}
	graphx->s_window.s_image.width = WINDOW_WIDTH;
	graphx->s_window.s_image.height = WINDOW_HEIGHT;
	game->screen_center = graphx->s_window.s_image.height / 2;
	ft_mlx_get_data_addr(&graphx->s_window.s_image);
	mlx_hook(graphx->s_window.mlx_win, ON_DESTROY, 0, &ft_on_destroy, game);
	mlx_hook(graphx->s_window.mlx_win, ON_KEYDOWN, (1L << 0), \
				&ft_key_handler, game);
	graphx->mouse_tracked = false;
	mlx_hook(graphx->s_window.mlx_win, ON_MOUSEMOVE, (1L << 6), \
				&ft_on_mouse_move, game);
	mlx_key_hook(graphx->s_window.mlx_win, &ft_key_up_handler, game);
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
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, &graphx->s_window.s_image.mlx_img)) /* need loop if add minimap */
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
		mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_IMAGE_ERROR);
	}
	graphx->s_window.s_image.width = WINDOW_WIDTH;
	graphx->s_window.s_image.height = WINDOW_HEIGHT;
	game->screen_center = graphx->s_window.s_image.height / 2;
	ft_mlx_get_data_addr(&graphx->s_window.s_image);
	mlx_hook(graphx->s_window.mlx_win, ON_DESTROY, 0, &ft_on_destroy, game);
	mlx_hook(graphx->s_window.mlx_win, ON_KEYDOWN, (1L << 0), &ft_key_handler, game);
	graphx->mouse_tracked = false;
	mlx_hook(graphx->s_window.mlx_win, ON_MOUSEMOVE, (1L << 6), &ft_on_mouse_move, game);
	mlx_key_hook(graphx->s_window.mlx_win, &ft_key_up_handler, game);
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

static void	ft_mlx_get_data_addr(t_image *image)
{
	image->data = mlx_get_data_addr(image->mlx_img, \
									&image->bits_per_pixel, \
									&image->size_line, \
									&image->endian);
}
