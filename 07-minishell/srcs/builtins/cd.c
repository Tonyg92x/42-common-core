/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 14:00:04 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Find the home path and if it does exist go there with chdir fonction
static void	go_home(t_command *command)
{
	char	*home;

	home = find_variable("HOME=", command->envp);
	if (!home)
		return ;
	chdir(home);
	change_pwd("PWD=", command->envp);
	free(home);
}

//	Go to the directory entered, if it's valid
static bool	change_dir(t_command *command)
{
	char	*ptr0;
	char	*ptr1;

	if (chdir(command->cmd[1]) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(command->cmd[1], 2);
		perror(":\b");
		command->queue_link->exit_status = 1;
		return (false);
	}
	command->queue_link->exit_status = 0;
	ptr0 = find_variable("PWD", command->queue_link->envp);
	ptr1 = ft_strjoin("OLDPWD=", ptr0);
	free(ptr0);
	update_envar(command->queue_link, ptr1);
	change_pwd("PWD=", command->queue_link->envp);
	free(ptr1);
	return (true);
}

void	builtin_cd(t_command *command)
{
	if (!command || !command->cmd || !command->cmd[0])
	{
		ft_putstr_fd("Invalid command entry\n", 2);
		command->queue_link->exit_status = 1;
	}
	else if (!command->cmd[1])
		go_home(command);
	else
		change_dir(command);
	update_exit_status(command->queue_link);
}
