/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 05:26:04 by aguay             #+#    #+#             */
/*   Updated: 2022/06/08 15:47:28 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

static void	render_player(t_game *game, int x, int y)
{
	const int	pos_x = x + ((int)game->player->x_pos % game->player->scale);
	const int	pos_y = y + ((int)game->player->y_pos % game->player->scale);

	mlx_putpixel(game->image.image, pos_x,
		pos_y, color_to_rgb(255, 255, 255));
}

static void	render_cadre(t_game *game)
{
	int	top;
	int	i;

	top = HEIGHT - (game->map_data->height * 13);
	i = 0;
	while (i < (game->map_data->width) * 12)
		mlx_putpixel(game->image.image, i++, top, color_to_rgb(0, 0, 0));
	while (top < HEIGHT - 1)
		mlx_putpixel(game->image.image, i, top++, color_to_rgb(0, 0, 0));
	while (i > 0)
		mlx_putpixel(game->image.image, i--, top, color_to_rgb(0, 0, 0));
	while (top > HEIGHT - (game->map_data->height * 13))
		mlx_putpixel(game->image.image, i, top--, color_to_rgb(0, 0, 0));
}

void	render_strip(t_game *game, int y, int pos_y, int pos_x)
{
	int	x;

	x = 0;
	while (pos_x < game->map_data->width)
	{
		if (game->map[pos_y][pos_x] && game->map[pos_y][pos_x] == '0')
			square_shape(&game->image, x, y, color_to_rgb(0, 0, 0));
		else if (game->map[pos_y][pos_x] && (ft_strchr ("NEWS",
								game->map[pos_y][pos_x])))
			square_shape(&game->image, x, y, color_to_rgb(0, 0, 0));
		else if (game->map[pos_y][pos_x] && game->map[pos_y][pos_x] == '1')
			square_shape(&game->image, x, y, color_to_rgb(125, 125, 0));
		else
			square_shape(&game->image, x, y, color_to_rgb(125, 125, 0));
			pos_x++;
			x += 12;
	}
	if (game->map
		[game->player->y_map]
		[game->player->x_map] \
			&& game->player->y_map == pos_y && game->player->x_map == pos_x)
		render_player(game, x, y);
}

void	render_map(t_game *game)
{
	int	y;
	int	pos_y;

	y = HEIGHT - (game->map_data->height * 13);
	pos_y = 0;
	while (pos_y <= game->map_data->height)
	{
		render_strip(game, y, pos_y, 0);
		y += 12;
		pos_y++;
	}
	render_cadre(game);
}
