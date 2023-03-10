/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdecale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:47:27 by aguay             #+#    #+#             */
/*   Updated: 2022/07/26 07:33:59 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Move every char in the string to the position before it to remove the index
//	0 of the string. If you want to remove a char, call this fonction with a
//	string pointer to the char in a string you want to remove.
char	*ft_strdecale(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}
