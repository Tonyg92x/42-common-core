/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:19:11 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/11 19:25:24 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"  
#include "stdlib.h"  

void	*ft_memchr(const void *src, int value, size_t num)
{
	unsigned char	*str;
	size_t			inc;

	inc = 0;
	str = (unsigned char *)src;
	while (inc < num)
	{
		if (*str != (unsigned char)value)
		{
			str++;
			inc++;
		}
		else
			return (str);
	}
	return (NULL);
}
