/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:15:05 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/14 17:13:53 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;
	char	*s;

	if (!dest && !src)
		return (NULL);
	i = -1;
	dst = (char *)dest;
	s = (char *)src;
	while (++i < n)
		dst[i] = s[i];
	return (dest);
}

size_t	search_endl(char *buffer)
{
	size_t	i;

	if (buffer[0] == '\0' || buffer[0] == '\n')
		return (0);
	i = 1;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		++i;
	}
	return (i - 1);
}


size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(char const *src, unsigned int n)
{
	unsigned int	i;
	char			*res;

	i = 0;
	while (src[i] && i < n)
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	while (src[i] && i < n)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (s1 && !s2)
		return (ft_strndup(s1, ft_strlen(s1)));
	if (s2 && !s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i + j == 0)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!dst)
		return (NULL);
	dst[i + j] = '\0';
	j = -1;
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[++j])
		dst[i + j] = s2[j];
	return (dst);
}
