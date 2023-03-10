/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/08 17:29:15 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	ft_last_cord(t_game *game, t_ray *ray)
{
	const float	offset = 0.0006;

	if (ray->dy < 0)
		ray->last_cordy = (int)((game->player->y_pos
					+ (ray->dy * ray->len) - offset) / game->player->scale);
	else
		ray->last_cordy = (int)((game->player->y_pos
					+ (ray->dy * ray->len) + offset) / game->player->scale);
	if (ray->dx < 0)
		ray->last_cordx = (int)((game->player->x_pos
					+ (ray->dx * ray->len) - offset) / game->player->scale);
	else
		ray->last_cordx = (int)((game->player->x_pos
					+ (ray->dx * ray->len) + offset) / game->player->scale);
	if (ray->last_cordy >= game->map_heigth)
		ray->last_cordy = game->map_heigth - 1;
	if (ray->last_cordy < 0)
		ray->last_cordy = 0;
	if (ray->last_cordx > (int)ft_strlen(game->map[
				ray->last_cordy]) || ray->last_cordx < 0)
		ray->last_cordx = (int)ft_strlen(game->map[ray->last_cordy]) - 1;
}

void	ft_nb_step(t_game *game, t_ray *ray)
{
	ray->map_rayx = (ray->pos_rayx / game->player->scale) + 1;
	ray->map_rayy = (ray->pos_rayy / game->player->scale) + 1;
	ft_nb_step_dx(game, ray);
	ft_nb_step_dy(game, ray);
}

int	raycaster(t_game *game, t_ray *ray, int i)
{
	ft_init_ray(game, ray, i);
	while (game->map[ray->last_cordy][ray->last_cordx] != '1')
	{
		ft_nb_step(game, ray);
		ft_dda(game, ray);
		ft_last_cord(game, ray);
	}
	ft_fixhit2(game, ray);
	ft_fishey(game, ray);
	ft_add_vertical(game, ray, i);
	return (0);
}

int	ray_fov(t_game *state)
{
	double	until;
	double	offset;
	double	increment;
	int		i;
	t_ray	ray;

	i = 0;
	offset = state->player->direction - PI / 6;
	until = state->player->direction + PI / 6;
	increment = ((state->player->direction
				+ PI / 6) - (state->player->direction - PI / 6)) / WIDTH;
	while (offset <= until)
	{
		ray.angle = ft_wrap_angle(offset);
		raycaster(state, &ray, i);
		offset += increment;
		i++;
	}
	fix_it_hihi(state);
	return (0);
}
