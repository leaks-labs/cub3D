#include "utils.h"

size_t	ft_len_till(char *str, char c);

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