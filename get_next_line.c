/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/11/13 20:55:00 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdint.h>
#include <stdio.h>

char	*ft_strndup(char const *src, unsigned int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

char	*first_step(int fd, char *buff, char **ptroldnlp, int *ret)
{
	char	*dst;
	char	*nlp;

	if (*ptroldnlp == 0)
	{
		*ret = read(fd, buff, BUFFER_SIZE);
		if (*ret <= 0)
			return (NULL);
		nlp = ft_strchr(buff, '\n');
		if (nlp)
			dst = (ft_strndup(buff, nlp - buff + 1));
		else
			dst = (ft_strndup(buff, *ret));
	}
	else
	{
		//ATTENTION SI '\n' vient d'un précédent appel du geneli, et qu'il n'est pas réellement dans la ligne
		nlp = ft_strchr(*ptroldnlp + 1, '\n');
		if (nlp)
		{
			dst = (ft_strndup(*ptroldnlp + 1, nlp - *ptroldnlp));
			printf("LOOL %ld\n", nlp - *ptroldnlp);
		}
		else
		{
			printf("LOL\n");
			dst = (ft_strndup(*ptroldnlp + 1, buff + *ret - *ptroldnlp - 1));
		}
	}
	*ptroldnlp = nlp;
	return (dst);
}

char	*build_string(int fd, char *buff, char **ptroldnlp, int *ret)
{
	char	*dst;
	char	*nlp;
	char	*tmp;

	nlp = NULL;
	dst = (char *)malloc(sizeof(char));
	dst[0] = '\0';
	while (!(nlp) && *ret)
	{
		/*
		if (*ret == -1)
		{
			free(buff);
			return (NULL);
		}
		*/
		*ret = read(fd, buff, BUFFER_SIZE);
		if (*ret == 0)
			break;
		nlp = ft_strchr(buff, '\n');
		tmp = dst;
		if (nlp == 0)
			dst = ft_strjoin(dst, ft_strndup(buff, *ret));
		else
			dst = ft_strjoin(dst, ft_strndup(buff, nlp - buff + 1));
		free(tmp);
	}
	*ptroldnlp = nlp;
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {0}; // Variable length array A CHANGER !
	static char	*oldnlp = NULL;
	static	int	ret = 1;
	char		*dst;
	char		*tmp;

	printf("buffer: '%s' ptrbuffer: %ld oldnlp: %ld\n", buff, (intptr_t)buff, (intptr_t)oldnlp);
	dst = first_step(fd, buff, &oldnlp, &ret);
	if (oldnlp)
		return (dst);
	tmp = dst;
	dst = ft_strjoin(dst, build_string(fd, buff, &oldnlp, &ret));
	free(tmp);
	return (dst);
}
