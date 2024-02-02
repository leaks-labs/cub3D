/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:26:19 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:37:06 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	const char	*s;

	s = src;
	if (n < 1)
		return (ft_strlen(src));
	while (*s && n-- > 1)
		*dst++ = *s++;
	*dst = '\0';
	return (ft_strlen(src));
}
