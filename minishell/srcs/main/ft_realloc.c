/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:41:53 by roxannefour       #+#    #+#             */
/*   Updated: 2022/09/07 09:32:26 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Get the number of strings in the string array.
static size_t	get_size(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i])
		i++;
	return (i + 2);
}

/*
	Dynamic memory tool.

	Add a new string array with the string added. Clean the memory of strings
	after. You should use it like this:
		string_array = ft_realloc(string_array, new_str);
*/
char	**ft_realloc(char **strings, char *str)
{
	char			**new_str;
	size_t			i;
	const size_t	size = get_size(strings);

	i = 0;
	new_str = ft_calloc(size, sizeof(char *));
	while (strings[i])
	{
		new_str[i] = strings[i];
		i++;
	}
	free(strings);
	new_str[i] = ft_strdup(str);
	new_str[i + 1] = NULL;
	return (new_str);
}
