/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/06 10:55:16 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	ft_rotate_left(t_game *game)
{
	initialise_map(game);
	game->player->direction -= 0.05;
	if (game->player->direction < 0)
		game->player->direction += 6.283;
	ray_fov(game);
}

void	ft_rotate_right(t_game *game)
{
	initialise_map(game);
	game->player->direction += 0.05;
	if (game->player->direction > 6.283)
		game->player->direction -= 6.283;
	ray_fov(game);
}
