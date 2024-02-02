/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:39:22 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:39:23 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_map	s_map;

	if (argc != 2)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (1 == ft_init_map(argv[1], &s_map) || 1 == ft_run(&s_map));
}
