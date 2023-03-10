/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:09:55 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 10:59:04 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Return how much command there is in the string array
static size_t	how_much_command(char **split_entry, size_t i, size_t length)
{
	size_t	retour;
	size_t	limit;

	if (!split_entry)
		return (0);
	retour = 0;
	limit = i + length;
	while (i <= limit && split_entry[i])
	{
		if (split_entry[i][0] == '|' && !split_entry[i][1])
			i++;
		else
		{
			retour++;
			i++;
		}
	}
	return (retour);
}

//	Initialise the exact size for of the command in command.cmd
bool	init_cmd(t_command *command, char **split_entry
	, size_t *i, size_t *length)
{
	size_t			cmd_entered;
	const size_t	cmd_to_entered = how_much_command(split_entry,
			(*i), (*length));

	if ((*length) == 0)
		return (false);
	command->cmd = ft_calloc(cmd_to_entered + 1, sizeof(char *));
	cmd_entered = 0;
	while (cmd_entered < cmd_to_entered)
		command->cmd[cmd_entered++] = ft_strdup(split_entry[(*i)++]);
	command->cmd[cmd_entered] = NULL;
	command->valid = true;
	return (true);
}

//	Return true if the path exist to the command.
static bool	is_command(char *command, t_command_q *command_q)
{
	const size_t	index_p = index_to_path(command_q->envp);
	char			**str;

	if (index_p == 999999)
		return (false);
	if (!command_q->envp || !command_q->envp[(int)index_p])
		return (false);
	str = ft_split(command_q->envp[(int)index_p], ':');
	if (str && !path_is_valid(command, str, command_q))
		return (false);
	return (true);
}

//	Look if the command is valid. If it is, parse it in the command
bool	command_exept(t_command_q *command_q, char **split_entry
	, size_t *i, size_t *length)
{
	if (!split_entry || !split_entry[(*i)])
		return (false);
	if (!is_command(split_entry[(*i)], command_q))
		return (false);
	if (!init_cmd(last_command(command_q), split_entry, i, length))
		return (true);
	return (true);
}
