/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 06:52:03 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:31:32 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pipe(t_command *command)
{
	int	*new_pipe;

	new_pipe = ft_calloc(2, sizeof(int));
	if (!new_pipe)
	{
		ft_putstr_fd("\033[31mError on allocating a new pipe\n \033[0m", 2);
		builtin_exit(command);
	}
	if (pipe(new_pipe) == -1)
	{
		ft_putstr_fd("minishell: pipe: ", 2);
		perror(" ");
		builtin_exit(command);
	}
	command->pipe_out = new_pipe;
	command->fd_out = new_pipe[1];
	command->next->fd_in = new_pipe[0];
	command->next->pipe_in = command->pipe_out;
}
