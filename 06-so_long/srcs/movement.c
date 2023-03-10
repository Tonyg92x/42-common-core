/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/03/29 09:29:27 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

void	move_a(t_vars *vars, int *char_x, int *char_y, t_map *map)
{
	if ((*char_x) >= 2)
	{
		if (map->pos[(*char_y)][(*char_x) - 1] != '1')
		{
			if (map->pos[(*char_y)][(*char_x) - 1] == '0')
				mov_0(vars, 'a');
			else if (map->pos[(*char_y)][(*char_x) - 1] == 'C')
			{
				put_char((*vars), ((*char_x) - 1) * 24, (*char_y) * 24);
				map->pos[(*char_y)][(*char_x) - 1] = '0';
				put_background((*vars), (*char_x) * 24, (*char_y) * 24);
				(*char_x)--;
				vars->map->nb_collectible--;
				if (vars->map->nb_collectible == 0)
					put_exit_open((*vars), map->exit_x * 24, map->exit_y * 24);
				ft_printf("Nombre de mouvements = %d\n",
					++vars->map->nb_movement);
			}
			else if (map->pos[(*char_y)][(*char_x) - 1] == 'E')
				won_event(vars);
		}
	}
}

void	move_s(t_vars *vars, int *char_x, int *char_y, t_map *map)
{
	if ((*char_y) < vars->map->height)
	{
		if (map->pos[(*char_y) + 1][(*char_x)] != '1')
		{
			if (map->pos[(*char_y) + 1][(*char_x)] == '0')
				mov_0(vars, 's');
			else if (map->pos[(*char_y) + 1][(*char_x)] == 'C')
			{
				put_char((*vars), (*char_x) * 24, ((*char_y) + 1) * 24);
				put_background((*vars), (*char_x) * 24, (*char_y) * 24);
				map->pos[(*char_x)][(*char_y) + 1] = '0';
				(*char_y)++;
				vars->map->nb_collectible--;
				if (vars->map->nb_collectible == 0)
					put_exit_open((*vars), map->exit_x * 24, map->exit_y * 24);
				ft_printf("Nombre de mouvements = %d\n",
					++vars->map->nb_movement);
			}
			else if (map->pos[(*char_y) + 1][(*char_x)] == 'E')
				won_event(vars);
		}
	}
}

void	move_d(t_vars *vars, int *char_x, int *char_y, t_map *map)
{
	if ((*char_x) < vars->map->width)
	{
		if (map->pos[(*char_y)][(*char_x) + 1] != '1')
		{
			if (map->pos[(*char_y)][(*char_x) + 1] == '0')
				mov_0(vars, 'd');
			else if (map->pos[(*char_y)][(*char_x) + 1] == 'C')
			{
				map->pos[(*char_y)][(*char_x) + 1] = '0';
				put_char((*vars), ((*char_x) + 1) * 24, (*char_y) * 24);
				put_background((*vars), (*char_x) * 24, (*char_y) * 24);
				(*char_x)++;
				vars->map->nb_collectible--;
				if (vars->map->nb_collectible == 0)
					put_exit_open((*vars), map->exit_x * 24, map->exit_y * 24);
				ft_printf("Nombre de mouvements = %d\n",
					++vars->map->nb_movement);
			}
			else if (map->pos[(*char_y)][(*char_x) + 1] == 'E')
				won_event(vars);
		}
	}
}

void	move_w(t_vars *vars, int *char_x, int *char_y, t_map *map)
{
	if ((*char_y) >= 2)
	{
		if (map->pos[(*char_y) - 1][(*char_x)] != '1')
		{
			if (map->pos[(*char_y) - 1][(*char_x)] == '0')
				mov_0(vars, 'w');
			else if (map->pos[(*char_y) - 1][(*char_x)] == 'C')
			{
				map->pos[(*char_y) - 1][(*char_x)] = '0';
				put_char((*vars), (*char_x) * 24, ((*char_y) - 1) * 24);
				put_background((*vars), (*char_x) * 24, (*char_y) * 24);
				(*char_y)--;
				vars->map->nb_collectible--;
				if (vars->map->nb_collectible == 0)
					put_exit_open((*vars), map->exit_x * 24, map->exit_y * 24);
				ft_printf("Nombre de mouvements = %d\n",
					++vars->map->nb_movement);
			}
			else if (map->pos[(*char_y) - 1][(*char_x)] == 'E')
				won_event(vars);
		}
	}
}
