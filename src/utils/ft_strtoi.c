#include "utils.h"

int32_t	ft_strtoi(char *nptr, bool *is_overflow)
{
	int32_t	res;
	int32_t	cpy;

	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		cpy = res;
		res = res * 10 + (int32_t)(*nptr - '0');
		if (res < cpy)
			return (*is_overflow = true);
		++nptr;
	}
	if (*nptr != '\0')
		return (*is_overflow = true);
	return (res);
}