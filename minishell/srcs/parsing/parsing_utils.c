/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/02 10:04:02 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Output and error message on stdError.
char	**error_exit(char **s_entry)
{
	if (s_entry)
		ft_free2d(s_entry);
	printf("\033[31mThere was an error while parsing :(.\033[0m\n");
	return (NULL);
}

//	Return true if it is a metacharacter that we need to parse
//	else return false.
bool	ft_is_metacharacter(char c)
{
	if (!c)
		return (false);
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

//	Same as ft_is_metacharacters but with sign & added.
//	It is usefull for parsing stupid user entry like <& that 
//	we should parse has, ignore the second metacharacter.
bool	ft_is_metacharacter_plus(char c)
{
	if (!c)
		return (false);
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '&')
		return (true);
	return (false);
}

//	Return the size of the word entered.
//	A word is delimited by the end of the entry or
//	by if the char is a metacharacter for a simple shell.
size_t	word_size(char *string)
{
	size_t	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i])
	{
		if (ft_is_metacharacter(string[i]))
			return (i);
		if (string[i] == '\'')
		{
			i++;
			while (string[i] != '\'')
				i++;
		}
		else if (string[i] == '"')
		{
			i++;
			while (string[i] != '"')
				i++;
		}
		i++;
	}
	return (i);
}
