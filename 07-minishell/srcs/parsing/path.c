/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:20:48 by aguay             #+#    #+#             */
/*   Updated: 2022/07/26 07:30:40 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Add a backslath after every string to test
//	test the path/command with acces funciton.
static char	**add_backslash(char **path)
{
	int		i;
	char	*path_command;

	i = 0;
	while (path[i])
	{
		path_command = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i++] = path_command;
	}
	return (path);
}

//	Return the index to the path variable in our envp
size_t	index_to_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] ==
			'A' && envp[i][2] == 'T' && envp[i][3] ==
			'H' && envp[i][4] == '=')
			return (i);
		i++;
	}
	return (999999);
}

//	Return true if the path work's else return false and free all memory
static bool	working_path(char **path, t_command_q *command_q, char *command)
{
	char		*temp;
	t_command	*path_command;
	int			i;

	i = 0;
	path_command = last_command(command_q);
	while (path[i])
	{
		temp = ft_strjoin(path[i], command);
		if (access(temp, F_OK) == 0)
		{
			path_command->path = temp;
			ft_free2d(path);
			return (true);
		}
		free(temp);
		i++;
	}
	ft_free2d(path);
	path_command->valid = false;
	return (false);
}

//	Return true if the path is valid.
bool	path_is_valid(char *command, char **path, t_command_q *command_q)
{
	char	**parsed_path;

	parsed_path = add_backslash(path);
	if (!working_path(parsed_path, command_q, command))
		return (false);
	return (true);
}
