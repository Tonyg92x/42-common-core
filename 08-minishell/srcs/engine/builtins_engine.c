/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_engine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:05:55 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 11:06:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_engine(t_command	*command, int *process_tab)
{
	if (!command || !command->cmd || !command->cmd[0])
		return ;
	if (ft_strnstr(command->cmd[0], "cd", 2) != NULL)
		builtin_cd(command);
	else if (ft_strnstr(command->cmd[0], "echo", 4) != NULL)
		builtin_echo(command);
	else if (ft_strnstr(command->cmd[0], "env", 3) != NULL)
		builtin_env(command);
	else if (ft_strnstr(command->cmd[0], "exit", 5) != NULL)
	{
		free(process_tab);
		builtin_exit(command);
	}
	else if (ft_strnstr(command->cmd[0], "export", 6) != NULL)
		builtin_export(command);
	else if (ft_strnstr(command->cmd[0], "pwd", 3) != NULL)
		builtin_pwd(command);
	else if (ft_strnstr(command->cmd[0], "unset", 5) != NULL)
		builtin_unset(command);
	else if (command->exit == true)
		builtin_status(command);
}
