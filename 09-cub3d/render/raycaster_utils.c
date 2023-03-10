/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/06 16:45:33 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

double	ft_fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

char	ft_what_face(t_ray *ray)
{
	if (ray->dx < 0 && ray->dy < 0)
	{
		if (ray->last_hit == 'x')
			return ('W');
		return ('N');
	}
	if (ray->dx < 0 && ray->dy > 0)
	{
		if (ray->last_hit == 'x')
			return ('W');
		return ('S');
	}
	if (ray->dx > 0 && ray->dy > 0)
	{
		if (ray->last_hit == 'x')
			return ('E');
		return ('S');
	}
	if (ray->dx > 0 && ray->dy < 0)
	{
		if (ray->last_hit == 'x')
			return ('E');
		return ('N');
	}
	return ('X');
}

void	ft_add_vertical(t_game *game, t_ray *ray, int i)
{
	const double	hauteur = (3000 / ray->len) / 2;
	const char		face = ft_what_face(ray);

	game->last_step = ray->last_hit;
	game->last_ray = face;
	game->ray = ray;
	render_texture(game, i, hauteur, 1);
}

void	ft_dda(t_game *game, t_ray *ray)
{
	if (ray->nb_step_x == ray->nb_step_y)
	{
		if (game->last_step == 'x')
			ray->nb_step_y++;
		else
			ray->nb_step_x++;
	}
	if (ray->nb_step_x < ray->nb_step_y)
		ft_step_x(ray);
	if (ray->nb_step_y < ray->nb_step_x)
		ft_step_y(ray);
}
