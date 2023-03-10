/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:34:59 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/06 09:06:47 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"

static unsigned int	nbr_lenght(long input, int sign)
{
	unsigned int	nbr_digit;

	nbr_digit = 0;
	if (input == 0)
		return (1);
	while (input > 0)
	{
		input /= 10;
		nbr_digit++;
	}
	if (sign == -1)
		nbr_digit++;
	return (nbr_digit);
}

static void	converter_nbr(char *str, long input, unsigned int ln, int sign)
{
	str[ln] = '\0';
	str[--ln] = input % 10 + '0';
	input /= 10;
	while (input > 0)
	{
		str[--ln] = input % 10 + '0';
		input /= 10;
	}
	if (sign == -1)
		str[0] = '-';
}

char	*ft_itoa(int input)
{
	char			*str;
	long			helper;
	unsigned int	nbr_digit;
	int				sign;

	sign = 1;
	if (input < 0)
	{
		helper = (long)input * -1;
		sign = -1;
	}
	else
		helper = input;
	nbr_digit = nbr_lenght(helper, sign);
	str = malloc(sizeof(char) * nbr_digit + 1);
	if (!str)
		return (NULL);
	converter_nbr(str, helper, nbr_digit, sign);
	return (str);
}
