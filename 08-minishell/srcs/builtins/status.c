/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 08:44:06 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 12:57:01 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Print the exit status of the last command executed
void	builtin_status(t_command *command)
{
	char	*ptr;

	if (command && command->queue_link)
	{
		ft_putstr_fd("minishell: ", 2);
		ptr = ft_itoa(command->queue_link->exit_status);
		ft_putstr_fd(ptr, 2);
		free(ptr);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(command->queue_link->exit_status), 2);
		ft_putstr_fd("\n", 2);
		command->queue_link->exit_status = 0;
	}
	else
		command->queue_link->exit_status = 1;
}
