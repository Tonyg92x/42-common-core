/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:59:56 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 16:05:17 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Have to clean other file created to here
//	(other created file could be fd used between
//	command without redirection)
static void	clean_routine(t_command_q *command_q)
{
	t_command	*temp;

	temp = command_q->start;
	while (temp)
	{
		if (temp->pipe_in)
		{
			close(temp->pipe_in[0]);
			close(temp->pipe_in[1]);
		}
		if (temp->pipe_out)
		{
			close(temp->pipe_out[0]);
			close(temp->pipe_out[1]);
		}
		if (temp->fd_in != 0)
			close(temp->fd_in);
		if (temp->fd_out != 1)
			close(temp->fd_out);
		unlink(temp->file_name);
		temp = temp->next;
	}
}

static void	ft_lunch_process(t_command *command, int *process_tab
	, int nb_process)
{
	int	id;

	id = fork();
	if (id == 0)
		command_engine(command);
	else
	{
		process_tab[nb_process] = id;
		if (command->pipe_in)
		{
			close(command->pipe_in[0]);
			close(command->pipe_in[1]);
		}
	}
}

static void	wait_loop(int nb_process, t_command_q *command_q
	, pid_t *process_tab)
{
	int			exit_status;
	int			index;
	t_command	*command;

	index = 0;
	command = command_q->start;
	while (nb_process > 0)
	{
		while (command->builtins)
			command = command->next;
		if (command->out_and_pipe && !command->prev->builtins)
			nb_process--;
		else
		{
			waitpid(process_tab[index++], &exit_status, 0);
			nb_process--;
			command_q->exit_status = WEXITSTATUS(exit_status);
		}
	}
	update_exit_status(command_q);
	free(process_tab);
}

static void	exec_loop(t_command *command, int *process_tab, int *nb_process)
{
	int	exit_status;

	while (command)
	{
		if (command->out_and_pipe)
		{
			if (command->prev->builtins == false)
			{
				wait(&exit_status);
				command->queue_link->exit_status = WEXITSTATUS(exit_status);
			}
			command->fd_in = open(command->prev->output, O_RDONLY);
		}
		if (command->builtins == true)
			builtins_engine(command, process_tab);
		else
		{
			ft_lunch_process(command, process_tab, (*nb_process));
			(*nb_process)++;
		}
		if (command->next)
			command = command->next;
		else
			break ;
	}
}

void	engine(t_command_q *command_q)
{
	t_command	*command;
	int			nb_process;
	int			*process_tab;

	nb_process = 0;
	ft_fdsetup(command_q->start);
	process_tab = ft_calloc(command_q->nb_command, sizeof(int));
	command = command_q->start;
	sig_chuttt();
	exec_loop(command, process_tab, &nb_process);
	wait_loop(nb_process, command_q, process_tab);
	signals();
	clean_routine(command_q);
}
