/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 04:16:36 by roxannefour       #+#    #+#             */
/*   Updated: 2022/09/09 14:03:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Look if the file can be open. It it can't return false else return true.
static bool	open_input(char *file)
{
	int	fd;

	if (ft_is_metacharacter(file[0]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, &file[0], 1);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		perror(" ");
		return (false);
	}
	else
		close(fd);
	return (true);
}

//	Parse the input
bool	ft_input(t_command *command, size_t *temp, size_t *len,
	char ***split_entry)
{
	ft_clear(split_entry, len, temp);
	if (!open_input((*split_entry)[(*temp)]))
		return (false);
	if (command->input)
		free(command->input);
	command->input = ft_strdup((*split_entry)[(*temp)]);
	if (command->here_doc)
		unlink(command->file_name);
	command->here_doc = false;
	ft_clear(split_entry, len, temp);
	return (true);
}
