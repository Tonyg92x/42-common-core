/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/02/08 13:34:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//	Switch the string in a long variable
long int	ft_atol(char	*string)
{
	long int	retour;
	int			i;
	int			negative;

	negative = 1;
	i = 0;
	retour = 0;
	if (string[i] == '-')
	{
		negative = -1;
		i++;
	}
	while (string[i] != '\0')
		retour = retour * 10 + (string[i++] - 48);
	return (retour * negative);
}
