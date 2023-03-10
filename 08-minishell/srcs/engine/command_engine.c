/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:08:29 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 14:43:52 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pre_exec(t_command *command)
{
	sigcancel();
	if (command->pipe_in)
		close(command->pipe_in[1]);
	if (command->pipe_out)
		close(command->pipe_out[0]);
	dup2(command->fd_in, 0);
	dup2(command->fd_out, 1);
}

void	command_engine(t_command *command)
{
	char	*path;
	char	**cmd;
	char	**envp;

	pre_exec(command);
	path = ft_strdup(command->path);
	cmd = ft_strsdup(command->cmd);
	envp = ft_strsdup(command->envp);
	ft_freeall(command);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd(cmd[0], 2);
		perror("\033[31m Error \033[0m");
		ft_free2d(cmd);
		if (path)
			free(path);
		ft_free2d(envp);
		exit(errno);
	}
}
