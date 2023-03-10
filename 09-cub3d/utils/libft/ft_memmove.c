/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:43:21 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/28 19:06:09 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include "stdlib.h" 

void	*ft_memmove(void *dst, const void *src, unsigned long len)
{
	unsigned char		*dst1;
	const unsigned char	*src1;

	dst1 = (unsigned char *)dst;
	src1 = (const unsigned char *)src;
	if (dst1 == src1)
		return (dst);
	else if (dst1 > src1)
	{
		src1 = src1 + len - 1;
		dst1 = dst1 + len - 1;
		while (len > 0)
		{
			*dst1 = *src1;
			dst1--;
			src1--;
			len--;
		}
	}
	else
		dst = ft_memcpy(dst1, src1, len);
	return (dst);
}
