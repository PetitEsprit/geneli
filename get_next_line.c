/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/20 11:11:48 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	search_endl(char *buffer);
size_t	ft_strlen(const char *s);

char	*extend_line(char *src, char *buffer, int *nl_found)
{
	char	*dst;
	char	*tmp;
	size_t	len;
	size_t	end;

	tmp = src;
	len = ft_strlen(src);
	end = search_endl(buffer);
	*nl_found = (buffer[end] == '\n');
	dst = (char *)malloc(sizeof(char) * (len + end + 2));
	if (!dst)
	{
		free(tmp);
		*nl_found = 1;
		return (NULL);
	}
	dst[len + end + 1] = '\0';
	ft_memcpy(dst, tmp, len);
	ft_memcpy(dst + len, buffer, end + 1);
	free(tmp);
	ft_memcpy(buffer, buffer + end + 1, BUFFER_SIZE - end);
	return (dst);
}

char	*build_string(int fd, char *buffer)
{
	char	*dst;
	int		ret;
	int		nl_found;

	nl_found = 0;
	dst = NULL;
	while (!nl_found)
	{
		if (!buffer[0])
		{
			ret = read(fd, buffer, BUFFER_SIZE);
			if (ret < 0)
			{
				free(dst);
				return (NULL);
			}
			else if (!ret || !buffer[0])
				return (dst);
			buffer[ret] = '\0';
		}
		dst = extend_line(dst, buffer, &nl_found);
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {0};
	char		*dst;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	dst = build_string(fd, buff);
	return (dst);
}
