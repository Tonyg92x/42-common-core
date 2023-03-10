/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:09:56 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 15:52:56 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	If it's a simple input, open the file and put
	his fd in fd_in. If it's a HD create the file
	and put his fd in fd_in.
	
	Note : limit of 127 - 32 commands.
*/
static void	setup_input(t_command *command)
{
	int		fd;

	if (command->input)
	{
		fd = open(command->input, O_RDONLY);
		if (fd > -1)
			command->fd_in = fd;
	}
	else if (command->here_doc)
	{
		fd = open(command->file_name, O_RDONLY);
		if (fd > -1)
			command->fd_in = fd;
	}
	else if (command->prev && !command->pipe_in)
		command->out_and_pipe = true;
}

/*
	If there is an output, open the file and put his fd
	in fd_out. If not and there is a next command, change
	fd_out for a created file to link them.
*/
static void	setup_output(t_command *command)
{
	int		fd;

	if (command->output && command->append_mode)
	{
		fd = open(command->output, O_WRONLY | O_APPEND);
		if (fd > -1)
			command->fd_out = fd;
	}
	else if (command->output)
	{
		fd = open(command->output, O_WRONLY | O_TRUNC);
		if (fd > -1)
			command->fd_out = fd;
	}
	else if (command->next)
		ft_add_pipe(command);
}

/*
	Prepare all commands to be runned

	a) If there is a here_doc, create the file for it and change the fd_in
		in the command. Then, open the file so it can be used.
	b) Open every input / output with correct options. fd value are stored 
		in fd_in or fd_out.
*/
void	ft_fdsetup(t_command *command)
{
	if (!command)
		return ;
	while (command)
	{
		setup_input(command);
		setup_output(command);
		command = command->next;
	}
}
