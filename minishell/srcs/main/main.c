/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 14:19:22 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_envp(char **envp, char **new_envp, int index, char *variable)
{
	new_envp[index] = ft_strdup(envp[find_variable_index(variable, envp)]);
	if (!new_envp)
	{
		new_envp[index] = ft_calloc(1, sizeof(char));
		new_envp[index][0] = '\0';
	}
}

static char	**small_envp_init(char **envp)
{
	char			**new_envp;
	size_t			i;

	i = 0;
	new_envp = ft_calloc(4, sizeof(char *));
	add_envp(envp, new_envp, i++, "_");
	add_envp(envp, new_envp, i++, "PWD");
	add_envp(envp, new_envp, i++, "SHLVL");
	return (new_envp);
}

//	Initialise every variable of command queue
static void	init_command_queue(t_command_q *command_q, char **envp, char **argv,
	int argc)
{
	int	index_old_pwd;

	command_q->start = NULL;
	command_q->nb_command = 0;
	command_q->exit_status = 0;
	if (argc > 1 && ft_strnstr(argv[1], "env", 5)
		&& ft_strnstr(argv[2], "-i", 2))
		command_q->envp = small_envp_init(envp);
	else
	{
		command_q->envp = envp_init(envp);
		index_old_pwd = find_variable_index("OLDPWD", command_q->envp);
		if (index_old_pwd != -1)
		{
			command_q->envp = ft_rev_realloc(command_q->envp,
					command_q->envp[index_old_pwd]);
		}
	}
	update_envar(command_q, "?=0");
	g_utils.command_q = command_q;
	g_utils.here_doc = NULL;
	g_utils.tokens = NULL;
}

//	Start of the program is here. argc and argv are there to be abble
//	to reach environnement variable in envp.
int	main(int argc, char **argv, char **envp)
{
	t_command_q	command_q;

	signals();
	init_command_queue(&command_q, envp, argv, argc);
	routine_prompt(&command_q);
}
