/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_operator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/08 13:45:21 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	paint_in_black(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
			mlx_putpixel(game->image.image, x, y++, color_to_rgb(0, 0, 0));
		x++;
	}
}

void	initialise_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
			mlx_putpixel(game->image.image, x, y++, color_to_rgb(
					game->map_data->ceiling_color [0],
					game->map_data->ceiling_color[1],
					game->map_data->ceiling_color[2]));
		while (y < HEIGHT)
			mlx_putpixel(game->image.image, x, y++, color_to_rgb(
					game->map_data->floor_color[0],
					game->map_data->floor_color[1],
					game->map_data->floor_color[2]));
		x++;
	}
}

void	fix_it_hihi(t_game *game)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
		mlx_putpixel(game->image.image, 0, y++, 0x000000);
}
