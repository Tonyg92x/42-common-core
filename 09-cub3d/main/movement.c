/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/09 15:23:33 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

static void	move_left(t_game *game)
{
	const double	angle = ft_wrap_angle(game->player->direction - 1.5708);
	const double	dx = cos(angle);
	const double	dy = sin(angle);
	const double	point_x = game->player->x_pos + dx;
	const double	point_y = game->player->y_pos + dy;

	if (is_in_wall(game, (point_x + dx) / game->player->scale,
			(point_y + dy) / game->player->scale))
	{
		game->player->x_pos = point_x;
		game->player->y_pos = point_y;
	}
}

static void	move_right(t_game *game)
{
	const double	angle = ft_wrap_angle(game->player->direction + 1.5708);
	const double	dx = cos(angle);
	const double	dy = sin(angle);
	const double	point_x = game->player->x_pos + dx;
	const double	point_y = game->player->y_pos + dy;

	if (is_in_wall(game, (point_x + dx) / game->player->scale,
			(point_y + dy) / game->player->scale))
	{
		game->player->x_pos = point_x;
		game->player->y_pos = point_y;
	}
}

static void	move_foward(t_game *game)
{
	double	point_x;
	double	point_y;

	point_x = game->player->x_pos + game->player->dx;
	point_y = game->player->y_pos + game->player->dy;
	if (is_in_wall(game, (point_x + game->player->dx) / game->player->scale,
			(point_y + game->player->dy) / game->player->scale))
	{
		game->player->x_pos = point_x;
		game->player->y_pos = point_y;
	}
}

static void	move_backward(t_game *game)
{
	double	point_x;
	double	point_y;

	point_x = game->player->x_pos - game->player->dx;
	point_y = game->player->y_pos - game->player->dy;
	if (is_in_wall(game, (point_x - game->player->dx) / game->player->scale,
			(point_y - game->player->dy) / game->player->scale))
	{
		game->player->x_pos = point_x;
		game->player->y_pos = point_y;
	}
}

void	move(t_game *game, char c)
{
	if (c == '+')
		move_foward(game);
	else if (c == '-')
		move_backward(game);
	else if (c == 'l')
		move_left(game);
	else if (c == 'r')
		move_right(game);
}
