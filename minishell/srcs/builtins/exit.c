/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigneau <jvigneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:37:11 by jvigneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Here we might need to change exit code ?
void	builtin_exit(t_command *command)
{
	int	exit_status;

	exit_status = 0;
	if (command && command->cmd && command->cmd[1]
		&& ft_isdigit(command->cmd[1][0]))
		exit_status = ft_atoi(command->cmd[1]);
	ft_freeall(command);
	exit (exit_status);
}
