/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemartel <jemartel@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:14:18 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/07 03:19:22 by jemartel         ###   ########.fr       */
/*   Created: 2022/06/06 05:26:04 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/06 14:29:21 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Include/cube.h"
#include "../utils/libft/libft.h"

static void	exit_routine(t_game *game)
{
	mlx_delete_image(game->mlx, game->image.image);
	freelist(game->map);
	exit(0);
	return ;
}

void	hook(void *param)
{
	t_mlx	*mlx;
	t_game	*state;

	state = param;
	mlx = state->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		exit_routine(state);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		ft_rotate_left(state);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		ft_rotate_right(state);
	hook_second(param);
}

void	hook_second(void *param)
{
	t_mlx	*mlx;
	t_game	*state;

	state = param;
	mlx = state->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		ft_move_w(state);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		ft_move_s(state);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		ft_move_d(state);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		ft_move_a(state);
}
