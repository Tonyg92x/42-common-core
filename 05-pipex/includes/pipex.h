/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/22 09:19:48 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>

typedef struct command
{
	struct command	*next;
	struct command	*prev;
	char			**cmd;
}								t_command;

typedef struct command_list
{
	struct command	*start;
	int				len;
}								t_command_list;

//	Command list fonctions
char	*get_cmd(char *string);
char	*get_arg(char *string);
void	initialise_command_list(t_command_list *l, int argc, char **argv);
void	free_command_list(t_command_list *l);
void	execute_command(t_command *command, char **envp, int *fd);
#endif
