/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 15:50:47 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_for_n(t_command *command, int i)
{
	int	j;

	j = 1;
	if (!command->cmd[i])
		return (false);
	if (command->cmd[i][0] == '-' && command->cmd[i][1] == 'n')
	{
		while (command->cmd[i][j] == 'n')
			j++;
		if (command->cmd[i][j] == '\0')
			return (true);
	}
	return (false);
}

static int	loop_echo(t_command *command, int i)
{
	if (g_utils.x == 0 && command->cmd[i][0]
		&& command->cmd[i][0] == '-' && check_for_n(command, i) == true)
		return (++i);
	else
		g_utils.x = 1;
	ft_putstr_fd(command->cmd[i], command->fd_out);
	i++;
	if (command->cmd[i])
		ft_putstr_fd(" ", command->fd_out);
	return (i);
}

void	builtin_echo(t_command *command)
{
	int		i;
	bool	n;

	if (!command || !command->cmd || !command->cmd[0])
	{
		ft_putstr_fd("Invalid command entry\n", 2);
		command->queue_link->exit_status = 1;
	}
	g_utils.x = 0;
	n = check_for_n(command, 1);
	if (n == true)
		i = 2;
	else
		i = 1;
	while (command->cmd[i])
		i = loop_echo(command, i);
	if (n == false)
		ft_putstr_fd("\n", command->fd_out);
	command->queue_link->exit_status = 0;
	g_utils.x = 0;
}
