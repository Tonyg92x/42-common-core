/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/06/20 09:38:52 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Free every adresse entered in the pointer of
//	pointers,then free the pointer of pointers.
void	ft_free2d(char **string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != NULL)
	{
		if (string[i])
			free(string[i]);
		i++;
	}
	if (string)
		free(string);
}
