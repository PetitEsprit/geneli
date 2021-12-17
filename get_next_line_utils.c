/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:15:05 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/17 16:58:32 by mdankou          ###   ########.fr       */
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

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*extend_line(char *src, char *buffer, size_t end)
{
	char	*dst;
	char	*tmp;
	size_t	len;

	tmp = src;
	len = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (len + end + 2));
	if (!dst)
	{
		free(tmp);
		return (NULL);
	}
	dst[len + end + 1] = '\0';
	ft_memcpy(dst, tmp, len);
	ft_memcpy(dst + len, buffer, end + 1);
	free(tmp);
	ft_memcpy(buffer, buffer + end + 1, BUFFER_SIZE - end); //update buffer
	return (dst);
}
