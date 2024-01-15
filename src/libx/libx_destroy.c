#include <stdlib.h>
#include "libx.h"

void	ft_destroy_graphx(t_graphx *graphx);

#ifdef __APPLE__

void	ft_destroy_graphx(t_graphx *graphx)
{
	/* could be a loop if minimap */
	mlx_destroy_image(graphx->mlx_ptr, graphx->s_window.s_image.mlx_img);
	mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
	free(graphx->mlx_ptr);
}

#elif __linux__

void	ft_destroy_graphx(t_graphx *graphx)
{
	mlx_loop_end(graphx->mlx_ptr);
	/* could be a loop if minimap */
	mlx_destroy_image(graphx->mlx_ptr, graphx->s_window.s_image.mlx_img);
	mlx_destroy_window(graphx->mlx_ptr, graphx->s_window.mlx_win);
	mlx_destroy_display(graphx->mlx_ptr);
	// free(graphx->mlx_ptr);
}

#endif
