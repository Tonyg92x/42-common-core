/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:13:41 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:00:17 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	double_quotes_except_hd(char **string, size_t *index)
{
	if (!is_closed(&((*string)[(*index)]), '"'))
		return (error_quotes());
	ft_strdecale(&(*string)[(*index)]);
	while ((*string)[(*index)] && (*string)[(*index)] != '"')
		(*index)++;
	ft_strdecale(&(*string)[(*index)]);
	return (true);
}

static void	no_expand_hd_name(char **ptr)
{
	size_t	i;

	i = 0;
	if (**ptr == '\'')
		single_quotes_except(ptr, &i);
	else if (**ptr == '"')
		double_quotes_except_hd(ptr, &i);
}

//	For every nodes, expand it
static bool	expand_entry(char ***split_entry, t_command *command)
{
	size_t	index;
	char	**ptr;
	bool	flag;

	flag = false;
	if (!split_entry || !(*split_entry) || !(*split_entry)[0])
		return (false);
	index = 0;
	while ((*split_entry) && (*split_entry)[index])
	{
		ptr = (&(*split_entry)[index]);
		if (**ptr == '<' && *(*ptr + 1) == '<')
			flag = true;
		if (flag == true)
			no_expand_hd_name(ptr);
		if (flag == false && !expand_node(ptr, command))
		{
			flag = false;
			return (false);
		}
		index++;
	}
	return (true);
}

/*	There is two execution possible here

	1)	First time called, no here doc can exist and it parse
		quotes and environnement variable's of the command nodes

	2)	Second time called, if an here doc is present, expand
		his environement variable's
*/
bool	expand_envar(t_command *command, char ***split_entry, size_t i)
{
	if (!command)
		return (false);
	else if (i == 0)
		return (expand_entry(split_entry, command));
	return (true);
}
