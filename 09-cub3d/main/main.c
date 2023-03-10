/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/08 15:10:24 by jemartel         ###   ########.fr       */
/*   Updated: 2022/06/06 14:20:41 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "../Include/cube.h"

void	argc_manager(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: wrong number of arguments expected a file \n", 1);
		exit(0);
	}
	else if (verify_extention(argv[1], ".cub") == 1)
	{
		ft_putstr_fd("Error: wrong file extension expected a .cub\n", 1);
		exit(0);
	}
}

t_game	*game_init(int argc, char **argv)
{
	t_game	*state;

	argc_manager(argc, argv);
	state = malloc(sizeof(t_game));
	state->map = NULL;
	state->player = malloc(sizeof(t_player));
	state->ray = NULL;
	state->player->scale = 10;
	state->map_data = init_map();
	state->map = map_init(mapcreator(argv[1]));
	return (state);
}

int	parser_validator(t_game *state)
{
	int	error;

	error = 0;
	error += parsing(state, 0);
	if (error > 0)
		return (printf("FROM  Parsing() line: %d at: %s\n", __LINE__, __FILE__));
	error += parse_location(state, 0, 0);
	if (error > 0)
		return (printf("Error\n:FROM parse_location() line: %d at:%s\n", __LINE__,
				__FILE__));
	error += validate_file (state);
	if (error > 0)
		printf("FROM validate_file() line: %d at:%s\n", __LINE__, __FILE__);
	return (error);
}

int	delete_this(t_game *state)
{
	freelist(state->map);
	delete_texture(state->map_data);
	free(state->player);
	free(state);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game		*state;

	state = game_init(argc, argv);
	if (parser_validator(state) > 0)
	{
		ft_putstr_fd ("Error \n", 1);
		return (delete_this(state));
	}
	init_this(state);
	mlx_loop_hook(state->mlx, &hook, state);
	mlx_loop(state->mlx);
	return (0);
}
