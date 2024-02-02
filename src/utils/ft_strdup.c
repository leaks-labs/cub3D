/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:55 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:26:14 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s1);

char	*ft_strdup(const char *s1)
{
	const size_t	size = ft_strlen(s1);
	char			*s2;

	s2 = ft_calloc(size + 1, sizeof(char));
	if (s2 != NULL)
		ft_memcpy(s2, s1, size + 1);
	return (s2);
}
