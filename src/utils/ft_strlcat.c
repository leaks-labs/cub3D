/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:26:16 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:26:17 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n);

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	d;

	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	d = ft_strlen(dst);
	if (d > n)
		return (ft_strlen(src) + n);
	while (src[i] && d + i < (n - 1))
	{
		dst[d + i] = src[i];
		++i;
	}
	dst[d + i] = '\0';
	return (ft_strlen(src) + d);
}
