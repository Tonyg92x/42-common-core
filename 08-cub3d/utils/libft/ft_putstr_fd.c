/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:50:59 by jean-phil         #+#    #+#             */
/*   Updated: 2022/06/06 16:24:19 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;
	int	b;

	i = 0;
	while (str[i])
	{
		b = write(fd, &str[i], 1);
		i++;
	}
	(void)b;
}
