/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:04 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/01/09 16:40:59 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

void		*ft_calloc(size_t count, size_t size);

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	f_size = size * count;
	void			*ptr;

	ptr = malloc(f_size);
	if (ptr != NULL)
		ft_memset(ptr, 0, f_size);
	return (ptr);
}
