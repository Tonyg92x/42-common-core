/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 12:30:28 by jean-phil         #+#    #+#             */
/*   Updated: 2021/06/10 14:58:04 by jean-phil        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"
#include "stdio.h"

static char	freelist(char **list, int index)
{
	while (index > 0)
	{
		free((void *) list[index]);
		index--;
	}
	free(list);
	return (0);
}

static char	*strmaker(const char *str, int index, int offset)
{
	char	*output;

	output = malloc(sizeof(char) * offset + 1);
	if (!output)
		return (0);
	ft_strlcpy(output, &str[index], offset + 1);
	return (output);
}

static char	**listmaker(const char *str, char **list, char cmp, int counter)
{
	int	index;
	int	offset;

	offset = 0;
	index = 0;
	while (str[index])
	{
		while (str[index + offset] != cmp && str[index + offset])
			offset++;
		if (offset == 0)
			index++;
		else
		{
			list[counter] = strmaker(str, index, offset);
			if (!list[counter])
			{
				freelist(list, counter);
				return (0);
			}
			counter++;
		}
		index += offset;
		offset = 0;
	}
	return (list);
}

static int	strcount(char const *str, char cmp)
{
	unsigned int	inc;
	unsigned int	nb_strs;

	if (!str[0])
		return (0);
	inc = 0;
	nb_strs = 0;
	while (str[inc] && str[inc] == cmp)
		inc++;
	while (str[inc])
	{
		if (str[inc] == cmp)
		{
			nb_strs++;
			while (str[inc] && str[inc] == cmp)
				inc++;
			continue ;
		}
		inc++;
	}
	if (str[inc - 1] != cmp)
		nb_strs++;
	return (nb_strs);
}

char	**ft_split(const char *str, char sep)
{
	char	**list;
	int		lenght;

	lenght = strcount(str, sep);
	if (!str)
		return (NULL);
	list = malloc(sizeof(char *) * (lenght + 1));
	if (!list)
		return (NULL);
	list = listmaker(str, list, sep, 0);
	list[lenght] = NULL;
	return (list);
}
