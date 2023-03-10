/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 08:04:14 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 13:31:06 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_envp_size(char **envp)
{
	size_t	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i + 1);
}

char	*find_variable(char *str, char **envp)
{
	size_t	i;
	size_t	start_pos;

	if (!str || !envp)
		return (NULL);
	i = 0;
	start_pos = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], str, ft_strlen(str)) != NULL)
		{
			while (envp[i][start_pos] && envp[i][start_pos] != '=')
				start_pos++;
			if (start_pos > ft_strlen(str))
				return (NULL);
			return (ft_strdup(&envp[i][++start_pos]));
		}
		i++;
	}
	return (NULL);
}

int	find_variable_index(char *str, char **envp)
{
	size_t	i;
	int		size_arg;
	int		size_envp;

	size_arg = 0;
	size_envp = 0;
	while (str[size_arg] && str[size_arg] != '=')
		size_arg++;
	if (!str || !envp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], str, ft_strlen(str)) != NULL)
		{
			while (envp[i][size_envp] && envp[i][size_envp] != '=')
				size_envp++;
			if (size_arg == size_envp)
				return (i);
		}
		i++;
	}
	return (-1);
}

//	Initialise our own envp variable, and increment the shell lvl
char	**envp_init(char **envp)
{
	char			**new_envp;
	char			*shell_lvl;
	const size_t	index = find_variable_index("SHLVL", envp);
	size_t			i;

	i = 0;
	new_envp = ft_calloc(get_envp_size(envp), sizeof(char *));
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	shell_lvl = new_envp[index];
	i = 0;
	while (shell_lvl && shell_lvl[i] && shell_lvl[i] != '=')
		i++;
	i++;
	shell_lvl[i] = (shell_lvl[i]) + 1;
	return (new_envp);
}

void	change_pwd(char *pwd, char **envp)
{
	const int	i = find_variable_index(pwd, envp);
	char		str[1000];
	char		*new_pwd;

	if (i == -1)
		return ;
	free(envp[i]);
	new_pwd = ft_strjoin(pwd, getcwd(str, sizeof(str)));
	envp[i] = ft_strdup(new_pwd);
	free(new_pwd);
}
