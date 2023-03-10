/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keysum_mac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:35:51 by aguay             #+#    #+#             */
/*   Updated: 2022/03/28 15:15:38 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

//  Initialise the keysum for debian
void	initialise_keysum(t_vars *vars)
{
	vars->escape = 53;
	vars->a = 0;
	vars->s = 1;
	vars->d = 2;
	vars->w = 13;
}
