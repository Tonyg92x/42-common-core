/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:37:41 by aguay             #+#    #+#             */
/*   Updated: 2022/08/31 12:28:44 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Return the length of the string entered.
size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str && str[count])
		count++;
	return (count);
}
