/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 14:51:25 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/28 19:18:53 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*fnptr)( unsigned int, char))
{
	int				i;
	unsigned int	len;
	char			*ptr;
	char			*copy;

	i = 0;
	len = ft_strlen(str) + 1;
	copy = malloc(sizeof(char) * len);
	if (!copy)
		return (NULL);
	ptr = copy;
	while (str[i])
	{
		*copy = (*fnptr)(i, str[i]);
		i++;
		copy++;
	}
	*copy = '\0';
	return (ptr);
}
