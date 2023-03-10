/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:37:51 by aguay             #+#    #+#             */
/*   Updated: 2022/06/23 09:23:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	needle_present(char *str, char *need)
{
	while (*str && *need)
	{
		if (*str != *need)
			return (false);
		str++;
		need++;
	}
	return (true);
}

//	Look for a string (needle) instide the other string (haystack).
//	Return the pointer to the start of the needle, otherwise return NULL.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*need;
	char	*retour;

	str = (char *)haystack;
	need = (char *)needle;
	if (ft_strlen(need) == 0)
		return ((char *)haystack);
	if (ft_strlen(haystack) < ft_strlen(needle))
		return (NULL);
	while (*str && len >= ft_strlen(needle))
	{
		if (*str == *need)
		{
			retour = str;
			if (needle_present(str, need))
				return (retour);
		}
		str++;
		len--;
	}
	return (NULL);
}
