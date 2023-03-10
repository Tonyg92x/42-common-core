/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 05:26:04 by aguay             #+#    #+#             */
/*   Updated: 2022/06/07 16:57:31 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Include/cube.h"
#include "../utils/libft/libft.h"

static void	exit_routine(t_game *game)
{
	mlx_delete_image(game->mlx, game->image.image);
	mlx_terminate(game->mlx);
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
	hook_second(param);
}

void	hook_second(void *param)
{
	t_mlx	*mlx;
	t_game	*state;

	state = param;
	mlx = state->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		ft_move_w(state);
		render_map(state);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		ft_move_s(state);
		render_map(state);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		ft_rotate_right(state);
		render_map(state);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		ft_rotate_left(state);
		render_map(state);
	}	
}
