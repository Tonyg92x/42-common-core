/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:26:17 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:26:25 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(t_command_q *command_q)
{
	char	*ptr;
	char	*ptr2;

	ptr = ft_itoa(command_q->exit_status);
	ptr2 = ft_strjoin("?=", ptr);
	free(ptr);
	update_envar(command_q, ptr2);
	free(ptr2);
}
