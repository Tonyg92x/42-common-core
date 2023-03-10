/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_until_this.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemartel <jemartel@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:57:11 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/07 15:57:18 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_until_this(char *str, char *this)
{
	int	inc;

	inc = -1;
	if (!str)
		return (-1);
	while (str[++inc])
	{
		if (ft_strchr(this, str[inc]))
			return (inc);
	}
	return (-1);
}
