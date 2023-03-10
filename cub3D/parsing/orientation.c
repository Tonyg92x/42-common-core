/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/06 05:35:45 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	player_direction(t_game *game)
{
	if (game->player->orientation == 'E')
		game->player->direction = deg_to_rad(1);
	else if (game->player->orientation == 'N')
		game->player->direction = deg_to_rad(271);
	else if (game->player->orientation == 'W')
		game->player->direction = deg_to_rad(181);
	else if (game->player->orientation == 'S')
		game->player->direction = deg_to_rad(91);
}
