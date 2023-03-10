/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 20:44:23 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/28 19:18:46 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*output;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	output = malloc(sizeof(char) * len + 1);
	if (!output)
		return (NULL);
	while (i != len)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
