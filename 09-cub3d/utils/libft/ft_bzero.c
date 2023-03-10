/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                           	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:26:34 by jean-phil         #+#    #+#             */
/*   Updated: 2021/08/12 15:41:38 by jean-phil        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_bzero(void *ptr, size_t num)

{
	unsigned char	*pted;

	pted = ptr;
	while (num--)
	{
		*pted++ = '\0';
	}
	return (ptr);
}
