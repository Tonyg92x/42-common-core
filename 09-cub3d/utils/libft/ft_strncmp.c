/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:06:49 by jean-phil         #+#    #+#             */
/*   Updated: 2022/06/06 09:06:20 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	unsigned int	val;

	val = 0;
	while (str1[val] != '\0' && str2[val] != '\0' && val < len)
	{
		if (str1[val] != str2[val])
		{
			return ((unsigned char) str1[val] - (unsigned char) str2[val]);
		}
		val++;
	}	
	if (str1[val] != str2[val] && val != len)
	{
		return ((unsigned char) str1[val] - (unsigned char) str2[val]);
	}
	return (0);
}
