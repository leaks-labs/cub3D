/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:35 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:25:36 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 42

static char	*ft_clear(char *buffer)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		++i;
	if ('\0' == buffer[i])
		return (ft_freef("%p", buffer));
	dst = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (NULL == dst)
		return (NULL);
	++i;
	j = 0;
	while (buffer[i] != '\0')
		dst[j++] = buffer[i++];
	dst[j] = '\0';
	free(buffer);
	return (dst);
}

static char	*ft_read(const char	*buffer)
{
	char	*dst;
	size_t	i;

	i = 0;
	if ('\0' == buffer[0])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		++i;
	dst = ft_calloc(i + 2, sizeof(char));
	if (NULL == dst)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		dst[i] = buffer[i];
		++i;
	}
	if ('\n' == buffer[i])
	{
		dst[i] = buffer[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_init(int fd, char *buffer)
{
	char		str[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		rd;

	if (NULL == buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (NULL == buffer)
		return (NULL);
	rd = 1;
	while (rd)
	{
		rd = read(fd, str, BUFFER_SIZE);
		if (-1 == rd)
			return (ft_freef("%p", buffer));
		str[rd] = '\0';
		tmp = buffer;
		buffer = ft_join(2, buffer, str);
		free(tmp);
		if (NULL == buffer)
			return (NULL);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (buffer);
}

char	*ft_get_next_line(int fd)
{
	char		*gnl;
	static char	*buffer;

	if (-1 == fd)
		return (NULL);
	buffer = ft_init(fd, buffer);
	if (NULL == buffer)
		return (NULL);
	gnl = ft_read(buffer);
	buffer = ft_clear(buffer);
	return (gnl);
}
