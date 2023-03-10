/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigneau <jvigneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:20:35 by jvigneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_command *command)
{
	char	*pwd;

	if (!command || !command->cmd || !command->cmd[0])
	{
		ft_putstr_fd("Invalid command entry\n", 2);
		command->queue_link->exit_status = 1;
	}
	if (command->cmd && command->cmd[1] && is_option(command->cmd[1]))
	{
		ft_putstr_fd("pwd : Invalid option\n", 2);
		command->queue_link->exit_status = 1;
	}
	pwd = find_variable("PWD", command->envp);
	ft_putstr_fd(pwd, command->fd_out);
	ft_putstr_fd("\n", command->fd_out);
	free(pwd);
	command->queue_link->exit_status = 0;
}
