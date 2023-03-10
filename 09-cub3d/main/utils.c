/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:38:26 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/08 15:09:44 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Include/cube.h"
#include "../utils/libft/libft.h"

void	free_list(t_dlist *head)
{
	t_dlist	*next;

	if (head != NULL)
	{
		next = head->next;
		free(head->content);
		free(head);
		free_list(next);
	}
}

char	freelist(char **list)
{
	int	inc;

	inc = 0;
	while (list && list[inc])
	{
		free(list[inc]);
		inc++;
	}
	free(list);
	return (0);
}

int	was_in_set(char *str, char *set)
{
	int	inc;
	int	cin;
	int	was_in_set;

	cin = 0;
	was_in_set = 1;
	inc = 0;
	while (str[inc])
	{
		while (set[cin])
		{
			if (set[cin] == str[inc])
			{
				was_in_set = 0;
				cin = 0;
				break ;
			}
			cin++;
		}
		if (was_in_set != 0)
			return (1);
		was_in_set = 1;
		inc++;
	}
	return (0);
}

void	init_map_size(t_game *game)
{
	size_t	height;
	size_t	width;

	width = 0;
	height = 0;
	while (game->map[height])
	{
		if (ft_strlen(game->map[height]) > width)
			width = ft_strlen(game->map[height]);
		height++;
	}
	game->map_data->width = (int)width;
	game->map_data->height = (int)height - 1;
}

void	init_this(t_game *state)
{
	t_image		image;

	resize_map(state, 0, 0, state->map_data->start);
	player_direction(state);
	state->player->x_pos = ((state->player->x_pos) * state->player->scale) + 1;
	state->player->y_pos = ((state->player->y_pos) * state->player->scale) + 1;
	state->player->x_map = (state->player->x_pos / state->player->scale) + 1;
	state->player->y_map = (state->player->y_pos / state->player->scale) + 1;
	state->last_step = 'x';
	state->mlx = mlx_init(800, 600, "./cube3d", 0);
	image.image = mlx_new_image(state->mlx, 800, 600);
	state->image = image;
	load_image(state);
	init_map_size(state);
	mlx_image_to_window(state->mlx, image.image, 0, 0);
	initialise_map(state);
	ray_fov(state);
}
