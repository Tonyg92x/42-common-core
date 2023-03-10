/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:13:22 by aguay             #+#    #+#             */
/*   Updated: 2022/07/26 07:13:31 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Calculate the offset to the index after the expanded variable
size_t	get_offset(char *string, size_t start, size_t len, bool hd)
{
	char	*variable;
	size_t	offset;

	variable = ft_substr(string, start, len);
	if (variable)
	{
		offset = ft_strlen(variable) + 2;
		if (hd)
			offset--;
		free(variable);
		return (offset);
	}
	return (0);
}

//	Get the environement variable value of the environnement variable in
//	string at the pos start. If it dosen't exist, return NULL.
char	*getex(char *string, size_t start, size_t len, char **envp)
{
	char	*variable;
	char	*expand;

	if (!string || start > ft_strlen(string) || len < 1)
		return (NULL);
	variable = ft_substr(string, start, len);
	expand = find_variable(variable, envp);
	if (variable)
		free(variable);
	return (expand);
}

//	Fonction to get to less then 25 lines for 42 norm.
void	ft_free_trash(char **string, char *ex, char *new_str)
{
	if ((*string))
		free((*string));
	if (ex)
		free(ex);
	(*string) = new_str;
}

//	Loop that keep characters before the variable in the new string
//	for the here doc.
void	ft_boucle_hd(char *string, size_t *i, size_t pos, char *new_str)
{
	while (string[(*i)] && (int)(*i) < (int)pos - 1)
	{
		new_str[(*i)] = string[(*i)];
		(*i)++;
	}
}

//	Loop that keep characters before the variable in the new string.
void	ft_boucle(char **string, size_t *i, size_t pos, char *new_str)
{
	while ((*string) && (*string)[(*i)] && (int)(*i) < (int)pos - 1)
	{
		if ((*string)[0] == '"')
			(*string)++;
		new_str[(*i)] = (*string)[(*i)];
		(*i)++;
	}
}
