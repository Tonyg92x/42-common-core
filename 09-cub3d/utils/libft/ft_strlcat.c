/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 15:50:21 by jean-phil         #+#    #+#             */
/*   Updated: 2021/06/08 10:36:13 by jean-phil        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dest_len;
	unsigned int	inc;

	dest_len = ft_strlen(dst);
	inc = 0;
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while (src[inc] && dest_len + inc < (size - 1))
	{
		dst[dest_len + inc] = src[inc];
		inc++;
	}
	dst[dest_len + inc] = '\0';
	return (ft_strlen(src) + dest_len);
}
