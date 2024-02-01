#include "utils.h"

size_t	ft_dptrlen(char **dptr)
{
	size_t	i;

	i = 0;
	while (dptr != NULL && dptr[i] != NULL)
		++i;
	return (i);
}
