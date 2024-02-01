# include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	const char	*s;

	s = src;
	if (n < 1)
		return (ft_strlen(src));
	while (*s && n-- > 1)
		*dst++ = *s++;
	*dst = '\0';
	return (ft_strlen(src));
}
