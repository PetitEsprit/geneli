/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/15 15:12:45 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	search_endl(char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_strndup(char const *src, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);

char	*build_string(char *buffer)
{
	size_t	end;
	size_t len;
	char	*dst;
	char *tmp;
	int	ret;

	dst = NULL;
	while (1)
	{
		if (!buffer[0])
		{
			ret = read(1, buffer, BUFFER_SIZE);
			if (ret < 1)
			{
				//clean
				//return
			}
			else if (!ret)
				return (dst);
			else
				buffer[ret] = '\0';
		}
		end = search_endl(buffer);
		len = ft_strlen(dst);
		tmp = dst;
		dst = (char *)malloc(sizeof(char) * (len + end + 1));
		if (!dst)
		{
			//clean
			//return
		}
		dst[len] = '\0';
		ft_memcpy(dst, tmp, len);
		ft_memcpy(dst + len, buffer, end);
		ft_memcpy(buffer, buffer + end + 1, BUFFER_SIZE - end + 1); //update buffer
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {0};
	char		*dst;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	dst = build_string(buff);
	return (dst);
}
