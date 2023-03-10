/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:13:32 by aguay             #+#    #+#             */
/*   Updated: 2022/09/21 11:03:25 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Add a fonction here that change the redirection for builtins here ?
	
	Output :
		If the builtins dosen't require an ouput, ignore it.
			else
				fork and dup2 the output and add a flag to the builtin
				to use exit ?

	Input :
		If the builtins dosen't require an iuput, ignore it.
			else
				any idea ?
*/

//	Look if the command passed in string is a builtins
bool	is_builtins(char *string)
{
	if (ft_strnstr(string, "cd", 2) != NULL && ft_strlen(string) == 2)
		return (true);
	if (ft_strnstr(string, "echo", 4) != NULL && ft_strlen(string) == 4)
		return (true);
	if (ft_strnstr(string, "env", 3) != NULL && ft_strlen(string) == 3)
		return (true);
	if (ft_strnstr(string, "exit", 4) != NULL && ft_strlen(string) == 4)
		return (true);
	if (ft_strnstr(string, "export", 6) != NULL && ft_strlen(string) == 6)
		return (true);
	if (ft_strnstr(string, "pwd", 3) != NULL && ft_strlen(string) == 3)
		return (true);
	if (ft_strnstr(string, "unset", 5) != NULL && ft_strlen(string) == 5)
		return (true);
	if (ft_strnstr(string, "$~", 2) != NULL && ft_strlen(string) == 2)
		return (true);
	return (false);
}

bool	is_option(char *str)
{
	while ((*str) && ((*str) == ' ' || (*str) == '\t'))
		str++;
	if ((*str) && (*str) == '-')
		return (true);
	return (false);
}
