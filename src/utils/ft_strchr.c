/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:48 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:26:09 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	const char	c2 = (const char)c;

	if (c2 == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s != c2)
		if (*s++ == '\0')
			return (NULL);
	return ((char *)s);
}
