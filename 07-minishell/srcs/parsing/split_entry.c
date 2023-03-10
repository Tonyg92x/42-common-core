/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/09/07 10:03:15 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getlesdeux(char *string, size_t *i)
{
	char	*retour;

	retour = ft_calloc(3, sizeof(char));
	retour[0] = string[0];
	retour[1] = string[1];
	retour[2] = '\0';
	(*i) += 2;
	return (retour);
}

char	*get_word(char *string, size_t *i)
{
	size_t			temp;
	size_t			index;
	char			*retour;
	const size_t	size = word_size(string);

	if (size == 0)
		return (NULL);
	temp = 0;
	(*i) += size;
	index = 0;
	retour = ft_calloc(size + 1, sizeof(char));
	if (!retour)
		return (NULL);
	while (temp < size)
		retour[index++] = string[temp++];
	retour[index] = '\0';
	return (retour);
}

char	*get_char(char c, size_t *i)
{
	char	*retour;

	retour = ft_calloc(2, sizeof(char));
	if (!retour)
		return (NULL);
	retour[0] = c;
	retour[1] = '\0';
	(*i)++;
	return (retour);
}

static void	parse_char(char **split_entry, char *entry, size_t *i, size_t *i_r)
{
	if (entry[*i + 1] && ((entry[(*i)] == '<' && ft_is_metacharacter_plus(
					entry[(*i) + 1])) || (entry[(*i)] == '>'
				&& ft_is_metacharacter_plus(entry[(*i) + 1]))))
		split_entry[(*i_r)] = getlesdeux(&entry[(*i)], i);
	else if (ft_is_metacharacter(entry[(*i)]))
		split_entry[(*i_r)] = get_char(entry[(*i)], i);
	else
		split_entry[(*i_r)] = get_word(&entry[(*i)], i);
	if (!split_entry[(*i_r)])
		error_exit(split_entry);
	(*i_r)++;
}

//	Split every node in a string array
char	**split_entry(char *entry, int nb_node)
{
	char			**split_entry;
	size_t			i;
	size_t			i_r;

	split_entry = ft_calloc(nb_node + 1, sizeof(char *));
	if (!split_entry)
		error_exit(split_entry);
	i = 0;
	i_r = 0;
	while (entry[i])
		parse_char(split_entry, entry, &i, &i_r);
	split_entry[i_r] = NULL;
	return (split_entry);
}
