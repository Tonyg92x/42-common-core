/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 13:16:31 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_start(char *str, char *ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (&str[i] == ptr)
			return (++i);
		i++;
	}
	return (-1);
}

static void	write_error_env(t_command *command)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(command->cmd[1], 2);
	ft_putstr_fd(": No such file or directory", 2);
	command->queue_link->exit_status = 1;
	ft_putstr_fd("\n", 2);
}

static void	single_var(t_command *command)
{
	int		i;
	int		start;
	char	*ptr;

	i = 0;
	while (command->envp[i])
	{
		start = find_start(command->envp[i], ft_strchr(command->envp[i], '='));
		ptr = ft_substr(command->envp[i], start, ft_strlen(command->envp[i]));
		if (ft_strnstr(command->cmd[1], ptr, ft_strlen(command->cmd[1]))
			&& (ft_strlen(command->cmd[1]) == ft_strlen(ptr)))
		{
			free(ptr);
			ft_putstr_fd(command->cmd[1], command->fd_out);
			ft_putstr_fd("\n", command->fd_out);
			command->queue_link->exit_status = 0;
			return ;
		}
		free(ptr);
		i++;
	}
	write_error_env(command);
}

static void	standard_env(t_command *command)
{
	size_t	i;

	i = 0;
	while (command->envp[i])
	{
		ft_putstr_fd(command->envp[i], command->fd_out);
		ft_putstr_fd("\n", command->fd_out);
		i++;
	}
	command->queue_link->exit_status = 0;
}

void	builtin_env(t_command *command)
{
	if (!command || !command->envp || !command->envp[0])
	{
		ft_putstr_fd("Error: no envp found.\n", 2);
		command->queue_link->exit_status = 1;
	}
	if (command->cmd && command->cmd[1] && is_option(command->cmd[1]))
	{
		ft_putstr_fd("env : Invalid option\n", 2);
		command->queue_link->exit_status = 1;
	}
	if (command->cmd[1])
		single_var(command);
	else
		standard_env(command);
}
