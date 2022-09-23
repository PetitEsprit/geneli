/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2022/09/19 19:36:24 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	search_endl(char *buffer);
size_t	ft_strlen(const char *s);

char	*extend_line(char *src, char *buffer, size_t n)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (len + n + 2));
	dst[len + n + 1] = '\0';
	ft_memcpy(dst, src, len);
	ft_memcpy(dst + len, buffer, n + 1);
	free(src);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {0};
	size_t		end;
	char		*dst;
	int			ret;
	int			nl_found;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	nl_found = 0;
	dst = NULL;
	while (!nl_found)
	{
		if (!buff[0])
		{
			ret = read(fd, buff, BUFFER_SIZE);
			if (!ret || !buff[0])
				return (dst);
			buff[ret] = '\0';
		}
		end = search_endl(buff);
		nl_found = (buff[end] == '\n');
		dst = extend_line(dst, buff, end);
		ft_memcpy(buff, buff + end + 1, BUFFER_SIZE - end);
	}
	return (dst);
}
