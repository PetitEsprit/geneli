/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/11/17 13:00:32 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s);
char	*ft_strndup(char const *src, unsigned int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

char	*first_step(int fd, char *buff, char **ptroldnlp, int *ret)
{
	char	*dst;
	char	*nlp;

	if (*ptroldnlp == 0)
	{
		*ret = read(fd, buff, BUFFER_SIZE);
		if (*ret <= 0)
			return (NULL);
		buff[*ret] = '\0';
		nlp = ft_strchr(buff, '\n');
		if (nlp)
			dst = (ft_strndup(buff, nlp - buff + 1));
		else
			dst = (ft_strndup(buff, *ret));
	}
	else
	{
		nlp = ft_strchr(*ptroldnlp + 1, '\n');
		if (nlp)
			dst = ft_strndup(*ptroldnlp + 1, nlp - *ptroldnlp);
		else
			dst = ft_strndup(*ptroldnlp + 1, buff + *ret - *ptroldnlp - 1);
	}
	*ptroldnlp = nlp;
	return (dst);
}

char	*build_string(int fd, char *buff, char **ptroldnlp, int *ret)
{
	char	*dst;
	char	*nlp;
	char	*tmp;
	char	*dup;

	nlp = NULL;
	dst = (char *)calloc(1, sizeof(char));
	while (!(nlp) && *ret)
	{
		*ret = read(fd, buff, BUFFER_SIZE);
		if (*ret == 0)
			break ;
		buff[*ret] = '\0';
		nlp = ft_strchr(buff, '\n');
		tmp = dst;
		if (nlp == 0)
			dup = ft_strndup(buff, *ret);
		else
			dup = ft_strndup(buff, nlp - buff + 1);
		dst = ft_strjoin(dst, dup);
		free(dup);
		free(tmp);
	}
	*ptroldnlp = nlp;
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {0};
	static char	*oldnlp = NULL;
	static int	ret = 1;
	char		*s[2];
	char		*dst;

	s[0] = first_step(fd, buff, &oldnlp, &ret);
	if (oldnlp || !s[0])
		return (s[0]);
	s[1] = build_string(fd, buff, &oldnlp, &ret);
	dst = ft_strjoin(s[0], s[1]);
	free(s[0]);
	free(s[1]);
	return (dst);
}
