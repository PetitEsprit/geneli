/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:08:59 by mdankou           #+#    #+#             */
/*   Updated: 2021/10/27 18:32:15 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "get_next_line.h"

t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(char const *src, int n);
size_t	ft_strlen(const char *s);

#include <stdio.h>
void printc(void * c)
{
	printf("%s\n", (char *)c);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

char	*build_string(t_list *l)
{
	char	*dst;
	t_list	*tmp;
	size_t	j;
	size_t	i;

	i = 0;
	tmp = l; 
	while (tmp)
	{
		i += ft_strlen((char *)tmp->content);
		tmp = tmp->next;
	}
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	i = 0;
	while (l)
	{
		j = -1;
		while (((char *)l->content)[++j])
			dst[i + j] = ((char *)l->content)[j];
		i+= j;
		l = l->next;
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	static char	*nlp = NULL;
	t_list		*first;
	t_list		*last;
	int			ret;

	if (nlp == 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			return (NULL);
		nlp = ft_strchr(buffer, '\n');
	}
	if (nlp == 0)
		last = ft_lstnew(ft_strndup(buffer, BUFFER_SIZE));
	else
		last = ft_lstnew(ft_strndup(nlp, BUFFER_SIZE - (nlp - buffer)));
	first = last;
	nlp = 0;
	ret = read(fd, buffer, BUFFER_SIZE);
	while (!((intptr_t)nlp > 0) && ret)
	{
		if (ret == -1)
		{
			ft_lstclear(&first, free);
			return (NULL);
		}
		nlp = ft_strchr(buffer, '\n');
		if (nlp == 0)
			last->next = ft_lstnew(ft_strndup(buffer, ret));
		else
			last->next = ft_lstnew(ft_strndup(buffer, nlp - buffer + 1));
		ret = read(fd, buffer, BUFFER_SIZE);
		last = last->next;
	}
	//ft_lstiter(first, printc);
	return (build_string(first));
}
