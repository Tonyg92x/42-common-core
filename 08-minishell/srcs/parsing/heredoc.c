/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:05:47 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 10:57:39 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**signal_exept(char **retour)
{
	char	*line;

	line = ft_calloc(1, sizeof(char));
	line[0] = '\0';
	retour = ft_realloc(retour, line);
	free(line);
	return (retour);
}

static char	**routine_hd(char *delim)
{
	char	**retour;
	char	*line;

	retour = ft_calloc(1, sizeof(char *));
	while (true)
	{
		g_utils.here_doc = retour;
		line = readline("> ");
		if (line == NULL)
			return (signal_exept(retour));
		if ((ft_strnstr(line, delim, ft_strlen(delim)) != NULL)
			&& ft_strlen(line) == ft_strlen(delim))
		{
			free(line);
			break ;
		}
		retour = ft_realloc(retour, line);
		free(line);
	}
	line = ft_calloc(1, sizeof(char));
	line[0] = '\0';
	retour = ft_realloc(retour, line);
	free(line);
	return (retour);
}

static void	prompt_hd(char *delim, t_command *command, char **split_entry)
{
	char	**retour;

	sigcancel();
	g_utils.tokens = split_entry;
	g_utils.command_q = command->queue_link;
	retour = routine_hd(delim);
	retour = expand_hd(retour, command);
	ft_create_file(retour, command->file_name);
	ft_free2d(retour);
	ft_free2d(split_entry);
	ft_freeall(command);
	exit(0);
}

//	Get the entry routine
static bool	get_hd(char *delim, t_command *command, char **split_entry)
{
	pid_t	id;
	int		status;

	if (delim && delim[0] && ft_is_metacharacter(delim[0]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, &delim[0], 1);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	status = 0;
	id = 0;
	if (access(command->file_name, F_OK) == 0)
		unlink(command->file_name);
	id = fork();
	sig_chuttt();
	if (id == 0)
		prompt_hd(delim, command, split_entry);
	else
		waitpid(id, &status, 0);
	signals();
	if (access(command->file_name, F_OK) != 0)
		return (false);
	command->here_doc = true;
	return (true);
}

//	Get the Here doc entry
bool	ft_input_hd(t_command *command, size_t *temp, size_t *len,
	char ***split_entry)
{
	ft_clear(split_entry, len, temp);
	if (!(*split_entry)[(*temp)])
	{
		ft_putstr_fd("Sytax error near unexpected token\n", 2);
		return (false);
	}
	if (!get_hd((*split_entry)[(*temp)], command, (*split_entry)))
		return (false);
	if (command->input)
	{
		free(command->input);
		command->input = NULL;
	}
	ft_clear(split_entry, len, temp);
	if (!(*split_entry)[(*temp)])
		command->valid = false;
	return (true);
}
