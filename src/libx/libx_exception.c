#include "libx.h"
#include "utils.h"

uint8_t ft_throw_mlx_exception(t_mlx_exception e_mlx_exception)
{
	const char mlx_exception[N_EXCEPTION][MLX_LEN_ERROR] = {
			MLX_INIT_ERROR,
			MLX_WINDOW_ERROR,
			MLX_IMAGE_ERROR,
	};
	t_mlx_exception e_exception;

	e_exception = INIT_ERROR;
	while (e_exception < N_EXCEPTION)
	{
		if (e_exception == e_mlx_exception)
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd(mlx_exception[e_exception], 2);
			return (1);
		}
		++e_exception;
	}
	return (0);
}
