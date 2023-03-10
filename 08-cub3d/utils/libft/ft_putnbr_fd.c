/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 07:46:10 by jean-phil         #+#    #+#             */
/*   Updated: 2022/06/06 16:20:49 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "libft.h"

static void	ft_putchar(char input, int fd)
{
	int	val;

	val = write(fd, &input, 1);
	(void)val;
}

void	ft_putnbr_fd(int input, int fd)
{
	unsigned int	nbr;

	if (input < 0)
	{
		nbr = (unsigned int)(-1 * input);
		ft_putchar('-', fd);
	}
	else
		nbr = (unsigned int)input;
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar(nbr + '0', fd);
}
