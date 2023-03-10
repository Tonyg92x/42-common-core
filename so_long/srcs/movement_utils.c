/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/03/29 09:29:40 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	mov_0_a(t_vars *vars)
{
	put_char((*vars), (vars->map->char_x - 1) * 24, vars->map->char_y * 24);
	put_background((*vars), (vars->map->char_x) * 24,
		vars->map->char_y * 24);
	vars->map->char_x--;
}

static void	mov_0_s(t_vars *vars)
{
	put_char((*vars), vars->map->char_x * 24, (vars->map->char_y + 1) * 24);
	put_background((*vars), vars->map->char_x * 24, vars->map->char_y * 24);
	vars->map->char_y++;
}

static void	mov_0_d(t_vars *vars)
{
	put_char((*vars), (vars->map->char_x + 1) * 24, vars->map->char_y * 24);
	put_background((*vars), vars->map->char_x * 24, vars->map->char_y * 24);
	vars->map->char_x++;
}

void	mov_0(t_vars *vars, char move)
{
	if (move == 'a')
		mov_0_a(vars);
	else if (move == 's')
		mov_0_s(vars);
	else if (move == 'd')
		mov_0_d(vars);
	else if (move == 'w')
	{
		put_char((*vars), vars->map->char_x * 24, (vars->map->char_y - 1) * 24);
		put_background((*vars), vars->map->char_x * 24, vars->map->char_y * 24);
		vars->map->char_y--;
	}
	ft_printf("Nombre de mouvements = %d\n", ++vars->map->nb_movement);
}

void	won_event(t_vars *vars)
{
	if (vars->map->nb_collectible <= 0)
	{
		ft_printf("You Won !\n");
		exit(0);
	}
}
