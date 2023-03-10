/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 15:00:25 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "libft.h"

typedef struct command
{
	size_t				index;
	struct command		*next;
	struct command		*prev;
	bool				valid;
	bool				builtins;
	bool				exit;
	char				**cmd;
	char				*path;
	char				*input;
	bool				here_doc;
	char				*output;
	bool				append_mode;
	char				**envp;
	struct command_q	*queue_link;
	int					fd_in;
	int					fd_out;
	char				file_name[4];
	int					*pipe_in;
	int					*pipe_out;
	bool				out_and_pipe;
}				t_command;

typedef struct command_q
{
	struct command	*start;
	size_t			nb_command;
	char			**envp;
	pid_t			exit_status;
}				t_command_q;

#endif
