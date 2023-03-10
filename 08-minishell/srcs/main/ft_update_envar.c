/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_envar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:06:43 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:16:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_name_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i == 0)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (-1);
		}
		else if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static bool	var_exist(char **envp, char *str, int *pos)
{
	const int	name_size = get_name_size(str);
	int			index;
	char		*ptr;

	if (name_size == -1)
		return (false);
	ptr = ft_substr(str, 0, name_size);
	index = 0;
	while (envp[index])
	{
		if (strnstr(envp[index], ptr, name_size))
		{
			(*pos) = index;
			free(ptr);
			return (true);
		}
		index++;
	}
	free(ptr);
	return (false);
}

void	update_envar(t_command_q *command_q, char *str)
{
	int	index;

	index = 0;
	if (var_exist(command_q->envp, str, &index))
	{
		command_q->envp = ft_rev_realloc(command_q->envp,
				command_q->envp[index]);
	}
	command_q->envp = ft_realloc(command_q->envp, str);
}
