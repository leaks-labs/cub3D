/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:33 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:25:50 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdarg.h>

char			*ft_join(int argc, ...);
static size_t	ft_get_len(int argc, va_list *aq);

char	*ft_join(int argc, ...)
{
	va_list	ap;
	va_list	aq;
	char	*tmp;
	char	*dst;
	size_t	len;

	va_start(ap, argc);
	va_copy(aq, ap);
	len = ft_get_len(argc, &aq);
	dst = ft_calloc(len + 1, sizeof(char));
	if (dst == NULL)
	{
		va_end(ap);
		return (NULL);
	}
	while (argc-- != 0)
	{
		tmp = va_arg(ap, char *);
		ft_strlcat(dst, tmp, len + 1);
	}
	va_end(ap);
	return (dst);
}

static size_t	ft_get_len(int argc, va_list *aq)
{
	int		i;
	size_t	len;

	i = -1;
	len = 0;
	while (++i < argc)
		len += ft_strlen(va_arg(*aq, char *));
	va_end(*aq);
	return (len);
}
