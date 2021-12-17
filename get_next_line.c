/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/17 16:36:33 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	search_endl(char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

void print_buffer(char *buff)
{
	int i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		if (isprint(buff[i]))
			printf("'%c'", buff[i]);
		else
			printf("'\\%d'", buff[i]);
		++i;
	}
	printf("\n");
}

char	*build_string(int fd, char *buffer)
{
	size_t	end;
	size_t len;
	char	*dst;
	char *tmp;
	int	ret;
	int nl_find;

	nl_find = 0; 
	dst = NULL;
	while (!nl_find)
	{
		if (!buffer[0])
		{
			ret = read(fd,  buffer, BUFFER_SIZE);
			//printf("ret: %d\n", ret);
			if (ret < 0)
			{
				//clean
				return (NULL);
			}
			else if (!ret || !buffer[0])
				return (dst);
			else
				buffer[ret] = '\0';
		}
		//print_buffer(buffer);
		end = search_endl(buffer);
		nl_find = (buffer[end] == '\n');
		len = ft_strlen(dst);
		tmp = dst;
		dst = (char *)malloc(sizeof(char) * (len + end + 2));
		if (!dst)
		{
			//clean
			return (NULL);
		}
		dst[len + end + 1] = '\0';
		ft_memcpy(dst, tmp, len);
		ft_memcpy(dst + len, buffer, end + 1);
		free(tmp);
		ft_memcpy(buffer, buffer + end + 1, BUFFER_SIZE - end); //update buffer
		//print_buffer(buffer);
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
