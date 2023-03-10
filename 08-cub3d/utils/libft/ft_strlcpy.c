/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 15:52:34 by jean-phil         #+#    #+#             */
/*   Updated: 2021/06/08 10:39:20 by jean-phil        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcpy(char *output, const char *src, size_t lenght)
{
	const size_t	len = ft_strlen(src);
	size_t			i;

	i = 0;
	if (lenght != 0)
	{
		while (src[i] != '\0' && i < lenght - 1)
		{
			output[i] = src[i];
			i++;
		}
		output[i] = '\0';
	}
	return (len);
}
