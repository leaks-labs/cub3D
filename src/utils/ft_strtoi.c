/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:26:33 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:36:34 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int32_t	ft_strtoi(char *nptr, bool *is_overflow)
{
	int32_t	res;
	int32_t	cpy;

	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		cpy = res;
		res = res * 10 + (int32_t)(*nptr - '0');
		if (res < cpy)
			return (*is_overflow = true);
		++nptr;
	}
	if (*nptr != '\0')
		return (*is_overflow = true);
	return (res);
}
