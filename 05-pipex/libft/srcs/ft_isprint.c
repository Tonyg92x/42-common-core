/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:36:43 by aguay             #+#    #+#             */
/*   Updated: 2022/03/15 09:07:33 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Return 1 (true) if the character entered
//	is printable. Return 0 (false) otherwise.
int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (1);
}
