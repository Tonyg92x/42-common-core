/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/23 08:55:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

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

static char	*working_path(char **path, int i, t_command *command)
{
	char	*retour;
	char	*path_command;

	i = 0;
	while (true)
	{
		if (path[i] == NULL)
			break ;
		path_command = ft_strjoin(path[i], command->cmd[0]);
		if (access(path_command, F_OK) == 0)
		{
			retour = ft_strdup(path[i]);
			free(path_command);
			return (retour);
		}
		free(path_command);
		i++;
	}
	return (NULL);
}

//	Get the path of the command that
//	I want to run.
static char	*get_path(char **envp, t_command *command)
{
	int		i;
	char	**path;
	char	*retour;

	i = 0;
	if (access(command->cmd[0], F_OK) == 0)
		return (strdup(command->cmd[0]));
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(&envp[i][5], ':');
			path = add_backslash(path);
			retour = working_path(path, i, command);
			ft_free2d(path);
			if (retour == NULL)
				return (NULL);
			else
				return (retour);
		}
		i++;
	}
	return (NULL);
}

//	Fonction to get less line in main.
static	void	exec_boucle(int *fd, char **envp, char *retour_stack,
	t_command *command)
{
	int		id;

	id = fork();
	if (id == 0)
	{
		close(fd[1]);
		if (execve(retour_stack, command->cmd, envp) == -1)
		{
			ft_putstr_fd("execve : command not found\n", 2);
			free(command);
			exit(0);
		}
	}
	else
		wait(&id);
}

//	Execute the command entered. If there is a problem,
//	do nothing and return.
void	execute_command(t_command *command, char **envp, int *fd)
{
	char	*path;
	char	*temp;
	char	retour_stack[400];

	if (command->cmd == NULL)
		return ;
	path = get_path(envp, command);
	temp = ft_strjoin(path, command->cmd[0]);
	free(path);
	ft_bzero(retour_stack, sizeof(retour_stack));
	if (temp != NULL)
		ft_strlcpy(retour_stack, temp, ft_strlen(temp) + 1);
	free(temp);
	if (retour_stack[0] != '\0')
		exec_boucle(fd, envp, retour_stack, command);
	else
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putstr_fd(command->cmd[0], 2);
		ft_putstr_fd("\n", 2);
	}
}
