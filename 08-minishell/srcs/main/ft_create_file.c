/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:11:53 by aguay             #+#    #+#             */
/*   Updated: 2022/09/08 13:11:12 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Create a file in the binary directory and enter strings in it separated
	by new line (s).

	strings	:	the content to enter in the file
	name	:	the name of the file

	You can use unlink() from unistd.h lib to delete a file
*/
void	ft_create_file(char **strings, char *name)
{
	int		fd;
	size_t	i;

	if (!name)
		return ;
	i = 0;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 1)
	{
		ft_putstr_fd("Error while opening the file.\n", 2);
		return ;
	}
	else
	{
		while (strings && strings[i])
		{
			ft_putstr_fd(strings[i++], fd);
			if (strings && strings[i])
				ft_putstr_fd("\n", fd);
		}
	}
	close(fd);
}
