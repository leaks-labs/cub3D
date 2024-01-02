#include "libx.h"
#include <stdlib.h>
void ft_destroy_graphx(t_graphx *graphx)
{
	// mlx_loop_end(graphx->mlx_ptr);
	/* could be a loop if minimap */
	mlx_destroy_image(graphx->mlx_ptr, graphx->window.image.mlx_img);
	mlx_destroy_window(graphx->mlx_ptr, graphx->window.mlx_win);
	// mlx_destroy_display(graphx->mlx_ptr);
	free(graphx->mlx_ptr);
}