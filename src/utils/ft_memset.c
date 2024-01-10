#include "utils.h"

void	*ft_memset(void *b, int c, size_t len);

void	*ft_memset(void *b, int c, size_t len)
{
	const unsigned char	uc_c = (const unsigned char)c;
	unsigned char		*uc_b;

	uc_b = (unsigned char *)b;
	while (len-- != 0)
		*uc_b++ = uc_c;
	return (b);
}
