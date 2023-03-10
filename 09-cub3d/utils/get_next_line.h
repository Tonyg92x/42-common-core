/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemartel <jemartel@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:40:34 by jemartel          #+#    #+#             */
/*   Updated: 2021/09/08 19:21:54 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  GET_NEXT_LINE_H
# define  GET_NEXT_LINE_H
# include "stdlib.h"
# include "fcntl.h"
# include "sys/stat.h"
# include "sys/types.h"
# include "unistd.h"
# include "stdio.h"

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchrr(char *head, int comp);
char	*ft_strjoin(char *first, char *second);
int		get_next_line(int fd, char **line);
# define BUFFSIZE 25

#endif
