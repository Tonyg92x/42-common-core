/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_analyser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 11:05:33 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	If we couldn't find the path to a command, get the command and args
//	and empty the path. Execve will give us the errno if we try to execute
//	with the wront path.
static bool	parsing_error(char **split_entry, size_t *i, size_t *length,
	t_command_q *command_q)
{
	t_command	*command;

	command = last_command(command_q);
	init_cmd(command, split_entry, i, length);
	if (access(command->cmd[0], F_OK) == 0)
	{
		command->path = ft_strdup(command->cmd[0]);
		command->valid = true;
		return (true);
	}
	command->path = ft_calloc(1, sizeof(char));
	command->path[0] = '\0';
	command->valid = false;
	return (true);
}

//	Look if there is a builtins command
bool	builtins_exept(t_command_q *command_q, char **split_entry,
	size_t *i, size_t *length)
{
	t_command	*command;

	if (!is_builtins(split_entry[(*i)]))
		return (false);
	command = last_command(command_q);
	command->builtins = true;
	if (split_entry[(*i)][0] && split_entry[(*i)][0] == '$'
		&& split_entry[(*i)][1] && split_entry[(*i)][1] == '~')
		command->exit = true;
	if (!init_cmd(command, split_entry, i, length))
		command->valid = false;
	return (true);
}

//	Parse the word to understand the command and his agruments.
static bool	parse_command(t_command_q *command_q, char **split_entry,
	size_t *i, size_t *length)
{
	size_t			i_limit;
	const t_command	*command = last_command(command_q);

	if ((command->here_doc || command->input || command->output)
		&& (*length) == 0)
		return (true);
	if ((*length) == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(split_entry[(*i)], 2);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	i_limit = (*i) + (*length);
	while (split_entry[(*i)] && (*i) < i_limit)
	{
		if (builtins_exept(command_q, split_entry, i, length))
			return (true);
		else if (command_exept(command_q, split_entry, i, length))
			return (true);
		else
			return (parsing_error(split_entry, i, length, command_q));
	}
	return (false);
}

//	Return the number of nodes in a command.
size_t	how_much_node_in_command(char **split_entry)
{
	size_t	index;

	index = 0;
	while (split_entry[index] && split_entry[index][0] != '|' )
		index++;
	return (index);
}

/*	Analyse every command with this algo.
	Algo :
		1) Create the command
		2) Get the number of node for the command in length variable
		3) Call expand environnement variable fonction that will
			expand the quotes, and environnement variable in the string
			array.
		4) Parse input or ouput in the command node's.
		5) Parse the command entry
		6) Expand environnement variable in here doc if there is one
		7) go to the next command
	
	Error possible :
		Quotes unclosed we only display and error message.
			note: Could add here doc to get the end of the entry like bash does
		No permissions to open an output file
		Can't open a file (path invalid or file missing)
*/	
bool	analyse_entry(t_command_q *command_q, char ***split_entry, int nb_node)
{
	size_t		i;
	size_t		length;
	t_command	*command;

	i = 0;
	while ((*split_entry)[i] && (int)i < nb_node)
	{
		command = new_command(command_q);
		length = how_much_node_in_command(&(*split_entry)[i]);
		if (!expand_envar(command, split_entry, 0))
			return (false);
		if (!ft_redir(command, split_entry, &length, &i))
			return (false);
		if (!parse_command(command_q, (*split_entry), &i, &length))
			return (false);
		if (!expand_envar(command, split_entry, 1))
			return (false);
		if ((*split_entry) && (*split_entry)[i] && (*split_entry)[i][0]
				&& (*split_entry)[i][0] == '|')
		i++;
	}
	return (true);
}
