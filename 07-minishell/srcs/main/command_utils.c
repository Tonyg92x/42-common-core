/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 15:00:51 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Setup all value of struct command to NULL
//	to avoid unwanted behavior
static void	initialise_command(t_command *command,
	t_command_q *command_q)
{
	command->valid = true;
	command->cmd = NULL;
	command->path = NULL;
	command->builtins = false;
	command->input = NULL;
	command->output = NULL;
	command->here_doc = false;
	command->append_mode = NULL;
	command->exit = false;
	command->out_and_pipe = false;
	command->envp = command_q->envp;
	command->queue_link = command_q;
	command->fd_in = 0;
	command->fd_out = 1;
	command->fd_in = 0;
	command->fd_out = 1;
	command->index = command_q->nb_command - 1;
	command->file_name[0] = '.';
	command->file_name[1] = 'H';
	command->file_name[2] = 33 + command->index;
	command->file_name[3] = '\0';
}

//	Return the pointer to the last command in the
//	queue.
t_command	*last_command(t_command_q *command_q)
{
	t_command	*temp;

	if (command_q->start == NULL)
		return (NULL);
	temp = command_q->start;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

//	Allocate a new command at the end of the queue.
t_command	*new_command(t_command_q *command_q)
{
	t_command	*temp;

	command_q->nb_command++;
	temp = last_command(command_q);
	if (temp == NULL)
	{
		command_q->start = ft_calloc(1, sizeof(t_command));
		initialise_command(command_q->start, command_q);
		return (command_q->start);
	}
	else
	{
		temp->next = ft_calloc(1, sizeof(t_command));
		initialise_command(temp->next, command_q);
		temp->next->prev = temp;
	}
	return (temp->next);
}

//	Free the comment and all attributes
void	free_command(t_command	*command)
{
	if (command == NULL)
		return ;
	if (command->path != NULL)
		free(command->path);
	if (command->cmd != NULL)
		ft_free2d(command->cmd);
	if (command->input != NULL)
		free(command->input);
	if (command->output != NULL)
		free(command->output);
	if (command->pipe_in != NULL)
		free(command->pipe_in);
	free (command);
}

//	Initilise the list of command and his flags.
//	Free the last list entered if there is one.
void	initialise_commands(t_command_q *command_q)
{
	t_command	*temp;

	command_q->nb_command = 0;
	if (command_q->start == NULL)
		return ;
	temp = command_q->start;
	while (temp && temp->next != NULL)
	{
		temp = temp->next;
		free_command(temp->prev);
	}
	if (temp)
		free_command(temp);
	command_q->start = NULL;
}
