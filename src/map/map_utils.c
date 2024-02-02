/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:15 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:45:48 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"

uint8_t	ft_check_extension(const char *str, const char *ext);
uint8_t	ft_open_file(const char *file, int32_t *fd);
char	*ft_read_line(char **str, int32_t fd, char to_skip);
size_t	ft_n_occurence(char *str, char c);
size_t	ft_len_till(char *str, char c);

uint8_t	ft_check_extension(const char *str, const char *ext)
{
	size_t	i;

	i = ft_strlen(str);
	while (str[i] != '.' && i != 0)
		--i;
	return (ft_strcmp(&str[i], ext) != 0);
}

uint8_t	ft_open_file(const char *file, int32_t *fd)
{
	*fd = open(file, O_RDONLY);
	return (-1 == *fd);
}

char	*ft_read_line(char **str, int32_t fd, char to_skip)
{
	*str = ft_get_next_line(fd);
	if (*str != NULL && to_skip == **str)
	{
		free(*str);
		ft_read_line(str, fd, to_skip);
	}
	return (*str);
}

size_t	ft_n_occurence(char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			++j;
		++i;
	}
	return (j);
}

size_t	ft_len_till(char *str, char c)
{
	const char	*s = str;

	while (*s != '\0')
	{
		if (c == *s)
			break ;
		++s;
	}
	return ((size_t)(s - str));
}
