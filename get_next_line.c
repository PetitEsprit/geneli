/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/14 19:32:29 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
size_t	search_endl(char *buffer)
size_t	ft_strlen(const char *s);
char	*ft_strndup(char const *src, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);

char	*build_string(char buffer)
{
	size_t	end;
	char	*dst;
	int	ret;

	dst = NULL;
	while (1)
	{
		if (!buffer[0])
		{
			ret = read(1, buffer, BUFFER_SIZE);
			if (ret < 1)
				//error
			else if (!ret)
				return (dst);
			else
				buffer[ret] = '\0';
		}
		end = search_endl(buffer);
		
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {0};
	char		*dst;
	
	return (dst);
}
