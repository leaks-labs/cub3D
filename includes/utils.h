#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>

void	*ft_calloc(size_t count, size_t size);
void	*ft_freef(const char *formats, ...);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
char	*ft_join(int argc, ...);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putstr_fd(const char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif