/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/22 10:30:30 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

//	Fonction to validate if the file is openable.
static bool	validate_file(char	*input, char *output)
{
	int	fd;

	fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error on opening the last file :");
		return (false);
	}
	else
		close(fd);
	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		perror("Error on opening the first file");
		return (false);
	}
	else
		close(fd);
	return (true);
}

static void	ft_pipex(t_command_list *list, char **argv, char **envp, int argc)
{
	t_command		*temp;
	int				fd[2];

	temp = list->start;
	dup2(open(argv[1], O_RDONLY), 0);
	while (list->len > 1)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe Error");
			return ;
		}
		dup2(fd[1], 1);
		execute_command(temp, envp, fd);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		temp = temp->next;
		list->len--;
	}
	if (list->len == 1)
	{
		dup2(open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777), 1);
		execute_command(temp, envp, fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*list;

	if (argc != 5)
	{
		ft_putstr_fd("The program need exactly 4 arguments.\n", 2);
		return (0);
	}
	if (validate_file(argv[1], argv[argc - 1]) == false)
		return (1);
	list = malloc(sizeof(t_command_list));
	initialise_command_list(list, argc, argv);
	if (list->len != 2)
	{
		free_command_list(list);
		return (0);
	}
	ft_pipex(list, argv, envp, argc);
	free_command_list(list);
}
