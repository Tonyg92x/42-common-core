/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:31:59 by jean-phil         #+#    #+#             */
/*   Updated: 2021/09/28 19:05:15 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *first, const void *second, size_t lenght)
{
	char	*helper_first;
	char	*helper_scd;

	helper_scd = (char *)second;
	helper_first = (char *)first;
	while (lenght-- > 0)
	{
		if (*helper_first != *helper_scd)
			return ((unsigned char)*helper_first - (unsigned char) *helper_scd);
		helper_first++;
		helper_scd++;
	}
	return (0);
}
