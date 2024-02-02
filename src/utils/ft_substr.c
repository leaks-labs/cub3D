/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:14 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:46:24 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(const char *s, unsigned int start, size_t len);

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr != NULL)
		ft_strlcpy(substr, (s + start), (len + 1));
	return (substr);
}
