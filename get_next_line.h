/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:09:31 by mdankou           #+#    #+#             */
/*   Updated: 2021/10/27 11:14:31 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H 
# define GET_NEXT_LINE_H 

typedef struct s_list
{
		void			*content;
		struct s_list	*next;
}						t_list;

char	*get_next_line(int fd);

#endif
