/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:18:11 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:23:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prompt_signal(t_command_q *command_q)
{
	printf("Minishel exiting...\n");
	ft_free2d(command_q->envp);
	exit(0);
}

void	ft_parsing_failed(t_command_q *command_q, char *entry)
{
	free(entry);
	initialise_commands(command_q);
}

void	ft_parsing_succes(t_command_q *command_q, char *entry)
{
	free(entry);
	engine(command_q);
	initialise_commands(command_q);
}
