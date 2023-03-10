/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fisheye.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/06 09:23:21 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

double	ft_wrap_angle(double angle)
{
	if (angle < 0.0)
		return (angle + 2.0 * PI);
	if (angle > 2.0 * PI)
		return (angle - 2.0 * PI);
	return (angle);
}

bool	ft_reste_eleve(float x)
{
	float	reste;

	reste = x - (int)x;
	if (reste > 0.999 || reste < 0.0008)
		return (true);
	return (false);
}

void	ft_fixhit2(t_game *game, t_ray *ray)
{
	if (ray->last_hit == 'x')
	{
		if (ray->last_hit != game->last_step && ft_reste_eleve
			(game->player->y_pos + (ray->dy * ray->len)))
			ray->last_hit = game->last_step;
	}
	if (ray->last_hit == 'y')
	{
		if (ray->last_hit != game->last_step && ft_reste_eleve
			(game->player->x_pos + (ray->dx * ray->len)))
			ray->last_hit = game->last_step;
	}
}

void	ft_fishey(t_game *game, t_ray *ray)
{
	float	theta;

	theta = ft_wrap_angle(game->player->direction - atan(ray->dy / ray->dx));
	ray->len = ft_fabs(ray->len * (cos(theta)));
}
