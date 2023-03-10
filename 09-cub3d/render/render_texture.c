/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by anthony           #+#    #+#             */
/*   Updated: 2022/06/06 16:17:22 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

void	render_texture(t_game *game, int i, double hauteur, int x)
{
	const t_mlx_image		*img = textur_to_draw(game);
	float					asset_height;
	float					asset_width;
	int						iterator;
	int						until;

	iterator = (HEIGHT / 2) + hauteur;
	until = (HEIGHT / 2) - hauteur;
	asset_width = 0;
	if (game->ray->last_hit == 'x')
		asset_width = (fmod(game->ray->pos_rayy, (double)game->player->scale)
				* img->width) / game->player->scale;
	if (game->ray->last_hit == 'y')
		asset_width = (fmod(game->ray->pos_rayx,
					game->player->scale) * img->width) / game->player->scale;
	while (iterator >= until)
	{
		asset_height = (x++ *(img->height - 1)) / (hauteur * 2);
		draw_pixel(game->image.image,
			i, iterator--,
			pixel_to_color((t_mlx_image *)img,
				(int)asset_width,
				(int)asset_height));
	}
}
