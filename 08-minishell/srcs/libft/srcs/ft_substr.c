/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:29:41 by jvigneau          #+#    #+#             */
/*   Updated: 2022/09/08 11:23:19 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ecrire une fct qui retourne une str qui start a start et max taille = len

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*final;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	final = ft_calloc(len + 1, sizeof(char));
	if (!final)
		return (NULL);
	i = start;
	if (start >= (ft_strlen(s)))
		return (final);
	while (s[i] && j < len)
	{
		final[j] = s[i];
		j++;
		i++;
	}
	return (final);
}
