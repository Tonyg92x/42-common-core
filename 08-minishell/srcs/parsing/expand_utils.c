/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:15:27 by aguay             #+#    #+#             */
/*   Updated: 2022/09/17 11:09:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Routine when there is a simple quotes
bool	single_quotes_except(char **string, size_t *index)
{
	if (!is_closed(&((*string)[(*index)]), '\''))
		return (error_quotes());
	ft_strdecale(&(*string)[(*index)]);
	while ((*string)[(*index)] && (*string)[(*index)] != '\'')
		(*index)++;
	ft_strdecale(&(*string)[(*index)]);
	return (true);
}

//	Routine when there is a double quotes
static bool	double_quotes_except(char **string, size_t *index
	, t_command *command)
{
	if (!is_closed(&((*string)[(*index)]), '"'))
		return (error_quotes());
	ft_strdecale(&(*string)[(*index)]);
	while ((*string)[(*index)] && (*string)[(*index)] != '"')
	{
		if ((*string)[(*index)] == '$')
		{
			if ((*string)[(*index) + 1] && (*string)[(*index) + 1] == '?')
			{
				(*string)[(*index) + 1] = '~';
				(*index) += 2;
			}
			else if (!expand_var(&(*string), ++(*index), command, false))
			{
				ft_clear_var(&(*string)[(*index) - 1],
					ft_strlen(&(*string)[(*index) - 1]));
				break ;
			}
		}
		(*index)++;
	}
	ft_strdecale(&(*string)[(*index)]);
	return (true);
}

//	Routine when there is no quotes
static bool	no_quotes_except(char **string, size_t *index
	, t_command *command)
{
	if ((*string)[0] == '$' && (*string)[1] && (*string)[1] == '?')
	{
		(*string)[1] = '~';
		(*index)++;
		return (true);
	}
	if (!expand_var(&(*string), ++(*index), command, false))
		ft_clear_var(&(*string)[(*index) - 1],
			ft_strlen(&(*string)[(*index) - 1]));
	return (true);
}

//	Expand environnement variable's in the string accordingly
//	to it's quotes presence.
bool	expand_node(char **string, t_command *command)
{
	size_t	index;

	if (!string || !(*string))
		return (false);
	index = 0;
	while ((*string) && (*string)[index])
	{
		if ((*string)[index] == '\'')
		{
			if (!single_quotes_except(string, &index))
				return (false);
		}
		else if ((*string)[index] == '"')
		{
			if (!double_quotes_except(string, &index, command))
				return (false);
		}
		else if ((*string)[index] == '$')
			no_quotes_except(string, &index, command);
		else
			index++;
	}
	return (true);
}
