/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_exception.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:24:08 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:44:43 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include <unistd.h>
#include "utils.h"

uint8_t	ft_throw_mlx_exception(t_mlx_exception e_mlx_exception);

uint8_t	ft_throw_mlx_exception(t_mlx_exception e_mlx_exception)
{
	const char	mlx_exception[N_EXCEPTION][MLX_LEN_ERROR] = {\
			MLX_INIT_ERROR, \
			MLX_WINDOW_ERROR, \
			MLX_IMAGE_ERROR,
	};

	if (e_mlx_exception < NO_EXCEPTION)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(mlx_exception[e_mlx_exception], STDERR_FILENO);
		return (1);
	}
	return (0);
}
