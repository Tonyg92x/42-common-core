/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:00:01 by aguay             #+#    #+#             */
/*   Updated: 2022/09/13 11:11:39 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	populate_new_str(char *ex, char *new_str, int offset)
{
	while (ex[g_utils.x])
		new_str[g_utils.i++] = ex[g_utils.x++];
	g_utils.x = g_utils.i - g_utils.x + offset;
	if (g_utils.x < ft_strlen((*g_utils.tokens))
		&& (*g_utils.tokens)[g_utils.x])
	{
		while (g_utils.x < ft_strlen((*g_utils.tokens))
			&& (*g_utils.tokens)[g_utils.x])
			new_str[g_utils.i++] = (*g_utils.tokens)[g_utils.x++];
	}
	else
		new_str[g_utils.i] = '\0';
	ft_free_trash(g_utils.tokens, ex, new_str);
	g_utils.i = 0;
	g_utils.i = 0;
	g_utils.tokens = NULL;
}

//	Expand every environnement variable in the string
bool	expand_var(char **string, int pos, t_command *command, bool hd)
{
	char			*ex;
	char			*new_str;
	const size_t	offset = get_offset((*string), pos,
			varlen(&(*string)[pos]), hd);

	ex = getex((*string), pos, varlen(&(*string)[pos]), command->envp);
	if (!ex)
		return (false);
	new_str = ft_calloc(ft_strlen((*string)) - varlen(&(*string)[pos])
			+ ft_strlen(ex) + 1, sizeof(char));
	g_utils.i = 0;
	g_utils.x = 0;
	g_utils.tokens = string;
	if (!hd)
		ft_boucle(string, &g_utils.i, pos, new_str);
	else
		ft_boucle_hd((*string), &g_utils.i, pos, new_str);
	populate_new_str(ex, new_str, offset);
	return (true);
}

//	Expand every string in the string array that the here doc has
char	**expand_hd(char **here_doc, t_command *command)
{
	size_t	i;
	size_t	x;

	i = 0;
	while (here_doc[i])
	{
		x = 0;
		while (here_doc[i][x])
		{
			if (here_doc[i][x] == '$')
			{
				if (!expand_var(&here_doc[i], ++x, command, true))
					ft_clear_var(&here_doc[i][x - 1],
						ft_strlen(&here_doc[i][x - 1]));
			}
			x++;
		}
		i++;
	}
	return (here_doc);
}
