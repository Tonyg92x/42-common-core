/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/08 16:29:56 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	ft_move_w(t_game *game)
{
	move(game, '+');
	initialise_map(game);
	ray_fov(game);
}

void	ft_move_s(t_game *game)
{
	move(game, '-');
	initialise_map(game);
	ray_fov(game);
}

void	ft_move_a(t_game *game)
{
	move(game, 'l');
	initialise_map(game);
	ray_fov(game);
}

void	ft_move_d(t_game *game)
{
	move(game, 'r');
	initialise_map(game);
	ray_fov(game);
}

bool	is_in_wall(t_game *game, int point_x, int point_y)
{
	if (point_y >= game->map_heigth - 1 || point_y <= 0 || point_x <= 0)
		return (false);
	if (game->map[point_y][point_x] && game->map[point_y][point_x] != '1')
		return (true);
	return (false);
}
