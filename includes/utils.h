/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:23:07 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:31:30 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

void	*ft_calloc(size_t count, size_t size);
size_t	ft_dptrlen(char **dptr);
void	*ft_freef(const char *formats, ...);
char	*ft_get_next_line(int fd);
char	*ft_join(int argc, ...);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putstr_fd(const char *s, int fd);
char	**ft_split(const char *str, const char sep);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int32_t	ft_strtoi(char *nptr, bool *is_overflow);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
