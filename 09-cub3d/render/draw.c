/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by aguay             #+#    #+#             */
/*   Updated: 2022/06/06 08:59:10 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h" 
#include <sys/types.h>
#include <unistd.h>

void	load_image(t_game *game)
{
	const t_mlx_tex	*temp = mlx_load_png(game->map_data->norh_texture);
	const t_mlx_tex	*temp2 = mlx_load_png(game->map_data->south_texture);
	const t_mlx_tex	*temp3 = mlx_load_png(game->map_data->est_texture);
	const t_mlx_tex	*temp4 = mlx_load_png(game->map_data->west_texture);

	game->map_data->north_tex = mlx_texture_to_image(game-> mlx,
			(t_mlx_tex *)temp);
	game->map_data->south_tex = mlx_texture_to_image(game-> mlx,
			(t_mlx_tex *)temp2);
	game->map_data->est_tex = mlx_texture_to_image(game-> mlx,
			(t_mlx_tex *)temp3);
	game->map_data->west_tex = mlx_texture_to_image(game-> mlx,
			(t_mlx_tex *)temp4);
	mlx_delete_texture((t_mlx_tex *) temp);
	mlx_delete_texture((t_mlx_tex *) temp2);
	mlx_delete_texture((t_mlx_tex *) temp3);
	mlx_delete_texture((t_mlx_tex *) temp4);
}

//	Cherche sur limage la bonne couleur.
uint32_t	pixel_to_color(t_mlx_image *tex, uint32_t x_pos, uint32_t y_pos)
{
	unsigned int	*pixel;
	uint32_t		temp;

	if (x_pos >= tex->width || y_pos >= tex->height)
		return (0);
	temp = x_pos + y_pos * tex->width;
	pixel = (unsigned int *)(tex->pixels +(temp) * sizeof(unsigned int));
	return (*pixel);
}

//	Ecrire sur la main window
void	draw_pixel(t_mlx_image *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t	*pixel;

	if (x >= img->width || y >= img->height)
		return ;
	pixel = (uint32_t *)&img->pixels[(x + y * img->width) * sizeof(uint32_t)];
	*pixel = color;
}

t_mlx_image	*textur_to_draw(t_game *game)
{
	if (game->last_ray == 'N')
		return (game->map_data->north_tex);
	if (game->last_ray == 'E')
		return (game->map_data->est_tex);
	if (game->last_ray == 'W')
		return (game->map_data->west_tex);
	if (game->last_ray == 'S')
		return (game->map_data->south_tex);
	return (NULL);
}
