/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splittin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:47:00 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 10:53:22 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Increment the index i until reach the end of double quote. If it dosen't
//	reach the end of double quotes, it is an unclosed quote error.
static bool	double_quote(char *string, int *i, int *count)
{
	(*i)++;
	(*count)++;
	while (string[(*i)])
	{
		if (string[(*i)] == '"')
		{
			(*i)++;
			return (true);
		}
		(*i)++;
	}
	ft_putstr_fd("\033[31mError:\033[0m Unclosed quotes\n", 2);
	return (false);
}

static bool	single_quote(char *string, int *i, int *count)
{
	(*i)++;
	(*count)++;
	while (string[(*i)])
	{
		if (string[(*i)] == '\'')
		{
			(*i)++;
			return (true);
		}
		(*i)++;
	}
	return (false);
}

static void	boucle_pipe_redir(char *string, int *i, int *count)
{
	while (string[(*i)] == '|')
	{
		(*count)++;
		(*i)++;
	}
	if (string[(*i) + 1] && ((string[(*i)] == '<' && string[(*i) + 1] == '<')
			|| (string[(*i)] == '>' && string[(*i) + 1] == '>')))
	{
		(*count)++;
		(*i) += 2;
	}
}

static int	boucle_quotes(char *string, int *i, int *count)
{
	if (string[(*i)] == '"')
	{
		if (!double_quote(string, i, count))
			return (9999999);
	}
	else if (string[(*i)] == '\'')
	{
		if (!single_quote(string, i, count))
			return (9999999);
	}
	return (0);
}

//	return the number of nodes in the user input
//	Should change the return 9999999 but a signal
//	to call an error quotes unclosed.
int	how_much_node(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string && string[i])
	{
		boucle_pipe_redir(string, &i, &count);
		if (boucle_quotes(string, &i, &count) == 9999999)
			return (9999999);
		if (ft_is_metacharacter(string[i]))
		{
			count++;
			i++;
		}
		else
		{
			count++;
			while (string[i] && !ft_is_metacharacter(string[i]))
				i++;
		}
	}
	return (count);
}
