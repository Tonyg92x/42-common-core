/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 11:07:42 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	unclosed_error(void)
{
	ft_putstr_fd("Error : Unclosed quotes\n", 2);
	return (false);
}

static bool	boucle_quotes(char *entry, int *i, char c)
{
	(*i)++;
	if (!entry[(*i)])
		return (unclosed_error());
	while (entry[(*i)] != c)
		(*i)++;
	if (!entry[(*i)])
		return (unclosed_error());
	return (true);
}

static bool	quotes_closed(char *entry)
{
	int	i;

	i = 0;
	while (entry && entry[i])
	{
		if (entry[i] == '\'')
		{
			if (!boucle_quotes(entry, &i, '\''))
				return (false);
		}
		else if (entry[i] == '"')
		{
			if (!boucle_quotes(entry, &i, '"'))
				return (false);
		}
		i++;
	}
	return (true);
}

static void	expand_exit(t_command_q *command_q)
{
	t_command	*command;
	char		*ptr;
	int			i;

	command = command_q->start;
	while (command)
	{
		i = 0;
		while (command->cmd && command->cmd[i])
		{
			if (command->cmd[i][0] && command->cmd[i][0] == '$'
				&& command->cmd[i][1] && command->cmd[i][1] == '~')
			{
				ptr = ft_itoa((int)command->queue_link->exit_status);
				free(command->cmd[i]);
				command->cmd[i] = ptr;
			}
			i++;
		}
		command = command->next;
	}
}

//	First step : get every word or important char
//	in different node for analysing. Then, analyse
//	the entry. If the return is NULL, there was an
//	error that bash usually just output an error and
//	go back to prompt.
bool	parsing(t_command_q *command_q, char *entry)
{
	char	**entry_sp;
	int		nb_node;

	if (!quotes_closed(entry))
		return (false);
	nb_node = how_much_node(entry);
	if (nb_node == 9999999)
		return (false);
	entry_sp = split_entry(entry, nb_node);
	ft_remove_space(&entry_sp);
	if (!entry_sp)
		return (false);
	if (!analyse_entry(command_q, &entry_sp, nb_node))
	{
		ft_free2d(entry_sp);
		return (false);
	}
	expand_exit(command_q);
	ft_free2d(entry_sp);
	return (true);
}
