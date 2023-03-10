/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigneau <jvigneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:06:36 by aguay             #+#    #+#             */
/*   Updated: 2022/09/07 11:43:16 by jvigneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Get the length of a variable in the string
size_t	varlen(char *string)
{
	size_t	retour;

	retour = 0;
	while (string[retour] && !ft_ismetaenv(string[retour]))
		retour++;
	return (retour);
}

//	True if the char is a metacharacter, else return false
bool	ft_ismetaenv(char c)
{
	return (c == '|' || c == '&' || c == ' ' || c == ';'
		|| c == '(' || c == ')' || c == '<' || c == '>'
		|| c == '\'' || c == '"');
}

//	Return false and output the error message that the quote isn't closed
bool	error_quotes(void)
{
	ft_putstr_fd("Parsing error: Quotes unclosed.\n", 2);
	return (false);
}

//	Fonction that clear the variable of the string by moving every char
//	after it to the left.
void	ft_clear_var(char *str, size_t limit)
{
	size_t	i;
	size_t	count;

	if (!str)
		return ;
	i = 0;
	count = 0;
	while (str[i] && count < limit && str[i] != ' ')
	{
		ft_strdecale(&str[i]);
		count++;
	}
}

bool	is_closed(char *string, char c)
{
	size_t	i;

	i = 1;
	while (string[i])
	{
		if (string[i] == c)
			return (true);
		i++;
	}
	return (false);
}
