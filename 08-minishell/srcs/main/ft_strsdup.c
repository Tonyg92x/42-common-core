/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:49:44 by aguay             #+#    #+#             */
/*   Updated: 2022/08/31 08:34:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Return the size of the longer string in envp
size_t	len_max(char **envp)
{
	size_t	i;
	size_t	y;
	size_t	retour;

	if (!envp || !envp[0])
		return (0);
	i = 0;
	retour = 0;
	while (envp[i])
	{
		y = 0;
		while (envp[i][y])
			y++;
		if (y > retour)
			retour = y;
		i++;
	}
	return (retour);
}

//	Return the number of strings in envp
size_t	strmax_size(char **strs)
{
	size_t	i;

	i = 0;
	if (!strs || !strs[0])
		return (0);
	while (strs[i])
		i++;
	return (i + 1);
}

//	Create a copy of strss
char	**ft_strsdup(char **strs)
{
	char	**retour;
	int		i;

	if (!strs)
		return (NULL);
	retour = ft_calloc(strmax_size(strs), sizeof (char *));
	i = 0;
	while (strs[i])
	{
		retour[i] = ft_strdup(strs[i]);
		i++;
	}
	retour[i] = NULL;
	return (retour);
}
