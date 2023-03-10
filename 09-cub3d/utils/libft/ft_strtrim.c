/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:40:12 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/28 19:20:38 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	int		inc;
	int		end;

	inc = 0;
	if (!str || !set)
		return (NULL);
	while (str[inc] && ft_strchr(set, str[inc]))
		inc++;
	end = ft_strlen(&str[inc]);
	if (end != 0)
		while (str[inc + end - 1] && ft_strchr(set, str[inc + end - 1]))
			end--;
	return (ft_substr(str, inc, end));
}
