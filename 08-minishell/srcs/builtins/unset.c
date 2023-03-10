/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 13:33:35 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_command *command)
{
	if (command->envp[find_variable_index(command->cmd[1], command->envp)])
		command->queue_link->envp = ft_rev_realloc(command->envp,
				command->envp[find_variable_index(command->cmd[1],
					command->envp)]);
	command->queue_link->exit_status = 0;
}
