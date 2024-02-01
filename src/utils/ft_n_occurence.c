#include "utils.h"

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
