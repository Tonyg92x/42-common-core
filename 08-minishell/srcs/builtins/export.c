/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 13:23:53 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	variable_name_verif(char *str, t_command_q *command_q)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_metacharacter(str[i]) || str[i] == '\'' || str[i] == '-'
			|| str[i] == '+' || str[i] == '/')
		{
			ft_putstr_fd("minishel: export: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			command_q->exit_status = 1;
			return (false);
		}
		if (i != 0 && str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

//	Export builtin add a variable to envp. if no arguments is passed, display
//	envp in alphabetic order.
void	builtin_export(t_command *command)
{
	if (!command || !command->cmd || !command->cmd[0])
	{
		ft_putstr_fd("Invalid command entry\n", 2);
		command->queue_link->exit_status = 1;
	}
	if (command->cmd && command->cmd[1] && is_option(command->cmd[1]))
	{
		ft_putstr_fd("env : Invalid option\n", 2);
		command->queue_link->exit_status = 1;
	}
	if (!command->cmd[1])
	{
		builtin_env(command);
		return ;
	}
	if (!ft_strchr(command->cmd[1], '=') && !ft_strchr(command->cmd[1], '+')
		&& !ft_strchr(command->cmd[1], '-') && !ft_strchr(command->cmd[1], '/'))
		return ;
	if (variable_name_verif(command->cmd[1], command->queue_link))
		update_envar(command->queue_link, command->cmd[1]);
}
