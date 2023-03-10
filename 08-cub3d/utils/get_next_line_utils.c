/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 10:26:02 by jean-phil         #+#    #+#             */
/*   Updated: 2021/10/05 13:10:27 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchrr(char *str, int compared)
{
	unsigned int	value;

	if (!str)
		return (NULL);
	value = 0;
	while (str[value])
	{
		if (str[value] == (char)compared)
		{
			return ((char *)&str[value]);
		}
		value++;
	}	
	if ((char)compared == str[value])
		return ((char *)&str[value]);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	char	*output;
	size_t	len;
	size_t	i;

	if (!str)
		return (NULL);
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
	output[len] = '\0';
	return (output);
}

char	*ft_strjoin(char *first, char *second)
{
	char		*output;
	size_t		len;
	size_t		len2;
	size_t		inc;

	inc = 0;
	len = ft_strlen(first);
	len2 = ft_strlen(second);
	if (!first)
		return (ft_strdup(second));
	output = malloc(sizeof(char) * len + len2 + 1);
	while (inc != len)
	{
		output[inc] = first[inc];
		inc++;
	}
	free(first);
	inc = 0;
	while (inc != len2)
	{
		output[len + inc] = second[inc];
		inc++;
	}
	output[len + len2] = '\0';
	return (output);
}
