/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:17:52 by aguay             #+#    #+#             */
/*   Updated: 2022/07/29 15:30:14 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Free everything allocated in the program
void	ft_freeall(t_command *command)
{
	ft_free2d(command->envp);
	initialise_commands(command->queue_link);
	rl_clear_history();
}
