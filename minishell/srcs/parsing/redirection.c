/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:42:58 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 10:57:01 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_input(char **split_entry, size_t temp, size_t limit)
{
	if (!split_entry[temp] || !split_entry[temp][0] || temp >= limit)
		return (false);
	temp++;
	if (temp >= limit || !split_entry[temp] || !split_entry[temp][0])
		return (false);
	return (true);
}

static bool	input_condition(size_t *temp, char ***split_entry,
	t_command *command, size_t *length)
{
	if ((*split_entry)[(*temp)][0] == '<')
	{
		if ((*split_entry)[(*temp)][1] && (*split_entry)[(*temp)][1] == '<')
		{
			if (ft_input_hd(command, temp, length, split_entry) == false)
				return (false);
		}
		else if ((*split_entry)[(*temp)][1] &&
			(!ft_is_metacharacter((*split_entry)[(*temp)][1])
			|| (*split_entry)[(*temp)][2]))
			return (true);
		else if (ft_input(command, temp, length, split_entry) == false)
			return (false);
	}
	else
		(*temp)++;
	return (true);
}

static bool	parse_input(t_command *command, char ***split_entry, size_t *length,
	size_t *i)
{
	size_t	limit;
	size_t	temp;

	temp = (*i);
	limit = temp + (*length);
	if ((limit - temp == 1) && ft_is_metacharacter((*split_entry)[(*i)][0]))
	{
		if ((*split_entry)[temp][1] &&
			(!ft_is_metacharacter((*split_entry)[temp][1])
			|| (*split_entry)[temp][2]))
			return (true);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (false);
	}
	while (valid_input((*split_entry), temp, limit))
	{
		if (!input_condition(&temp, split_entry, command, length))
			return (false);
	}
	return (true);
}

bool	parse_output(t_command *command, char ***split_entry, size_t *len,
	size_t *i)
{
	size_t	limit;
	size_t	temp;

	temp = (*i);
	limit = temp + (*len);
	while (valid_input((*split_entry), temp, limit))
	{
		if ((*split_entry)[temp][0] == '>')
		{
			if ((*split_entry)[temp][1] && (*split_entry)[temp][1] == '>')
			{
				if (ft_append(command, &temp, len, split_entry) == false)
					return (false);
			}
			else if ((*split_entry)[temp][1] &&
				(!ft_is_metacharacter((*split_entry)[temp][1])
				|| (*split_entry)[temp][2]))
				return (true);
			else if (ft_output(command, &temp, len, split_entry) == false)
				return (false);
		}
		else
			temp++;
	}
	return (true);
}

/*
	Parse the redirection of every node in the command. For every
	input/output or append mode, get the name of the file, look if
	the open option works and if it does; enter the input in the
	command structure and remove the node's associated with the
	input/ouput of the string array, reduce the length of the command.
	This way at the end, there is only the command left to parse. Every
	time an input or ouput his parse, if there is an entry already in the
	command that contredict the entry, remove it and free the memory
	assicoated. Bash only use the last input or output in a command.

	at last, if the open option dosen't work on the file, return false
	and the parsing of the entry end here.
*/
bool	ft_redir(t_command *command, char ***split_entry, size_t *length,
	size_t *i)
{
	if (!parse_input(command, split_entry, length, i))
		return (false);
	if (!parse_output(command, split_entry, length, i))
		return (false);
	return (true);
}
