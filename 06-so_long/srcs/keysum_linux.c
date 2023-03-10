/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keysum_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:35:51 by aguay             #+#    #+#             */
/*   Updated: 2022/03/28 15:15:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

//  Initialise the keysum for debian
void	initialise_keysum(t_vars *vars)
{
	vars->escape = 65307;
	vars->a = 97;
	vars->s = 115;
	vars->d = 100;
	vars->w = 119;
}
