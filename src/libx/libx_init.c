#include "libx.h"
// #include <X11/X.h>

static void *ft_mlx_init(void **mlx_ptr);
static void *ft_mlx_new_window(void *mlx_ptr, void **mlx_win);
static void *ft_mlx_new_image(void *mlx_ptr, void **mlx_img);
static void ft_mlx_get_data_addr(t_image *image);

t_mlx_exception ft_init_graphx(t_game_data *game_data, t_graphx *graphx)
{
	if (NULL == ft_mlx_init(&graphx->mlx_ptr))
		return (INIT_ERROR);
	if (NULL == ft_mlx_new_window(graphx->mlx_ptr, &graphx->window.mlx_win))
	{
		// mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_WINDOW_ERROR);
	}
	if (NULL == ft_mlx_new_image(graphx->mlx_ptr, &graphx->window.image.mlx_img)) /* need loop if add minimap */
	{
		mlx_destroy_window(graphx->mlx_ptr, graphx->window.mlx_win);
		// mlx_destroy_display(graphx->mlx_ptr);
		return (CREATE_IMAGE_ERROR);
	}
	ft_mlx_get_data_addr(&graphx->window.image);
	mlx_hook(graphx->window.mlx_win, 2, (1L << 0), &ft_key_handler, game_data);
	return (NO_EXCEPTION);
}

static void *ft_mlx_init(void **mlx_ptr)
{
	*mlx_ptr = mlx_init();
	return (*mlx_ptr);
}

static void *ft_mlx_new_window(void *mlx_ptr, void **mlx_win)
{
	*mlx_win = mlx_new_window(mlx_ptr, 500, 500, (char *)"cub3d");
	return (*mlx_win);
}

static void *ft_mlx_new_image(void *mlx_ptr, void **mlx_img)
{
	*mlx_img = mlx_new_image(mlx_ptr, 500, 500);
	return (*mlx_img);
}

static void ft_mlx_get_data_addr(t_image *image)
{
	image->data = mlx_get_data_addr(image->mlx_img,
									&image->bits_per_pixel,
									&image->size_line,
									&image->endian);
}