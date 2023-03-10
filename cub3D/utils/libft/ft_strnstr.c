/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:25:50 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/28 19:21:04 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	inc;
	size_t	it;

	inc = 0;
	it = 0;
	if (*str2 == '\0')
		return ((char *)&str1[0]);
	while (str1[inc] && inc < len)
	{
		if (str1[inc] == str2[0])
		{
			while (str2[it] && str1[inc + it] && str1[inc + it] == str2[it])
			{
				if (!((inc + it) < len))
					break ;
				it++;
			}
		}
		if (str2[it] == '\0')
			return ((char *)&str1[inc]);
		it = 0;
		inc++;
	}
	return (NULL);
}
