/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:53:29 by jean-phil         #+#    #+#             */
/*   Updated: 2022/06/07 15:56:57 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"

void	ft_putendl_fd(char *str, int fd)
{
	int		i;
	int		b;
	char	nl;

	nl = '\n';
	i = 0;
	while (str[i])
	{
		b = write(fd, &str[i], 1);
		i++;
	}
	i = write(fd, &nl, 1);
	(void)b;
}
