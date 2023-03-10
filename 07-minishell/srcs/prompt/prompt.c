/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 14:17:48 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_color(char *str, char *color, size_t *i)
{
	size_t	j;

	j = 0;
	while (color[j])
		str[(*i)++] = color[j++];
}

static void	add_var(char *var, char *prompt, size_t *i)
{
	size_t	j;

	j = 0;
	while (var[j])
		prompt[(*i)++] = var[j++];
	if (var)
		free(var);
}

static char	*get_prompt(t_command_q	*command_q)
{
	char	*prompt;
	char	*user;
	char	*pwd;
	size_t	i;

	i = 0;
	user = find_variable("USER", command_q->envp);
	pwd = find_variable("PWD", command_q->envp);
	if (user)
	{
		prompt = ft_calloc(ft_strlen(user) + ft_strlen(pwd) + 30, sizeof(char));
		add_color(prompt, "\033[32m", &i);
		add_var(user, prompt, &i);
	}
	else
		prompt = ft_calloc(ft_strlen(pwd) + 30, sizeof(char));
	if (pwd)
	{
		add_color(prompt, "\033[31m@\033[33m", &i);
		add_var(pwd, prompt, &i);
	}
	add_color(prompt, "\033[31m-> \033[0m\0", &i);
	return (prompt);
}

//	This is the prompt routine that get user input
void	routine_prompt(t_command_q *command_q)
{
	char	*entry;
	char	*prompt;

	initialise_commands(command_q);
	while (true)
	{
		prompt = get_prompt(command_q);
		entry = readline(prompt);
		free(prompt);
		if (entry && entry[0] != '\0' && entry[0] != ' ')
			add_history(entry);
		if (entry == NULL)
			ft_prompt_signal(command_q);
		if (!parsing(command_q, entry))
			ft_parsing_failed(command_q, entry);
		else
			ft_parsing_succes(command_q, entry);
	}
	rl_clear_history();
	return ;
}
