/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 23:06:39 by jean-phil         #+#    #+#             */
/*   Updated: 2021/06/07 15:46:08 by jean-phil        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdlib.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*helper_src;
	unsigned char	*helper_dest;

	helper_src = (unsigned char *)src;
	helper_dest = (unsigned char *)dst;
	while (n > 0 && *helper_src != (unsigned char) c)
	{
		n--;
		*helper_dest++ = *helper_src++;
	}
	if (n > 0)
	{
		*helper_dest++ = (unsigned char)*helper_src++;
		return ((void *)helper_dest);
	}
	else
		return (NULL);
}
