/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 20:06:50 by jean-phil         #+#    #+#             */
/*   Updated: 2021/05/17 15:22:45 by jean-phil        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_calloc(unsigned long lenght, unsigned long size)
{
	void	*p;

	p = malloc(lenght * size);
	if (!p)
		return (NULL);
	return (ft_memset(p, 0, lenght * size));
}
