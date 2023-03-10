/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/05 07:54:42 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	ft_init_ray(t_game *game, t_ray *ray, int i)
{
	ray->len = 0;
	ray->dx = cos(ray->angle);
	ray->dy = sin(ray->angle);
	ray->pos_rayx = game->player->x_pos;
	ray->pos_rayy = game->player->y_pos;
	if (i == WIDTH / 2)
	{
		game->player->dx = ray->dx;
		game->player->dy = ray->dy;
	}
	ray->last_cordy = (int)(game->player->y_pos
			+ (ray->dy * ray->len)) / game->player->scale;
	ray->last_cordx = (int)(game->player->x_pos
			+ (ray->dx * ray->len)) / game->player->scale;
}

void	ft_nb_step_dx(t_game *game, t_ray *ray)
{
	double	next_case;

	next_case = 0;
	if (ray->dx < 0)
	{
		next_case = (ray->map_rayx - 1) * game->player->scale;
		if (ray->pos_rayx == (ray->map_rayx - 1) * game->player->scale)
			next_case = ray->map_rayx * game->player->scale;
		ray->nb_step_x = ft_fabs((ray->pos_rayx - next_case) / ray->dx);
	}
	else
	{
		next_case = ray->map_rayx * game->player->scale;
		if (ray->pos_rayx == ray->map_rayx * game->player->scale)
			next_case = (ray->map_rayx + 1) * game->player->scale;
		ray->nb_step_x = (next_case - ray->pos_rayx) / ray->dx;
	}
}

void	ft_nb_step_dy(t_game *game, t_ray *ray)
{
	double	next_case;

	next_case = 0;
	if (ray->dy < 0)
	{
		next_case = (ray->map_rayy - 1) * game->player->scale;
		if (ray->pos_rayy == (ray->map_rayy - 1) * game->player->scale)
			next_case = ray->map_rayy * game->player->scale;
		ray->nb_step_y = ft_fabs((ray->pos_rayy - next_case) / -ray->dy);
	}
	else
	{
		next_case = ray->map_rayy * game->player->scale;
		if (ray->pos_rayy == ray->map_rayy * game->player->scale)
			next_case = (ray->map_rayy + 1) * game->player->scale;
		ray->nb_step_y = (next_case - ray->pos_rayy) / ray->dy;
	}
}

void	ft_step_x(t_ray *ray)
{
	ray->last_hit = 'x';
	ray->len += ray->nb_step_x;
	while (ray->nb_step_x > 1)
	{
		ray->pos_rayx += ray->dx;
		ray->pos_rayy += ray->dy;
		ray->nb_step_x--;
	}
	ray->pos_rayx += ray->dx * ray->nb_step_x;
	ray->pos_rayy += ray->dy * ray->nb_step_x;
}

void	ft_step_y(t_ray *ray)
{
	ray->last_hit = 'y';
	ray->len += ray->nb_step_y;
	while (ray->nb_step_y > 1)
	{
		ray->pos_rayx += ray->dx;
		ray->pos_rayy += ray->dy;
		ray->nb_step_y--;
	}
	ray->pos_rayx += ray->dx * ray->nb_step_y;
	ray->pos_rayy += ray->dy * ray->nb_step_y;
}
