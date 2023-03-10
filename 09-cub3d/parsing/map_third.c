/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_third.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemartel <jemartel@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:01:32 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/09 11:32:35 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h" 

int	any_one_above_line(t_game *map, int current_line)
{
	int	inc;

	inc = 0;
	while (map->map[current_line][inc])
	{
		if (map->map[current_line][inc] == '0')
		{
			if (any_one_above(map, current_line, inc))
				return (assert(1, "something is above\n"));
		}
		inc++;
	}
	return (0);
}

int	any_one_bellow_line(char **map, int current_line)
{
	int	inc;

	inc = 0;
	while (map[current_line][inc])
	{
		if (map[current_line][inc] == '0')
		{
			if (any_one_bellow(map, current_line, inc))
				return (assert(1, "missing  wall at the bottom\n"));
		}
		inc++;
	}
	return (0);
}

int	any_one_bellow(char **map, int current_line, int pos)
{
	while (map[current_line])
	{
		current_line++;
		if (map[current_line] && pos <= (int)ft_strlen(map[current_line]))
		{
			if (map[current_line][pos] == '1')
				return (0);
			else if (map[current_line][pos] == ' ')
				return (1);
			else
				continue ;
		}
		if (pos > (int)ft_strlen(map[current_line]))
			return (1);
		else if (map[current_line - 1][pos] && (map
			[current_line - 1][pos] == '1'))
			return (0);
	}
	return (0);
}

int	validate_file(t_game *game)
{
	int	file;

	file = open(game->map_data->norh_texture, R_OK);
	if (file > 0)
		close(file);
	else
		return (assert(1, "wrong file NORTH\n"));
	file = open(game->map_data->est_texture, R_OK);
	if (file > 0)
		close(file);
	else
		return (assert(1, "wrong file EST\n"));
	file = open(game->map_data->west_texture, R_OK);
	if (file > 0)
		close(file);
	else
		return (assert(1, "wrong file WEST\n"));
	file = open(game->map_data->south_texture, R_OK);
	if (file > 0)
		close(file);
	else
		return (assert(1, "wrong file south_texture\n"));
	return (0);
}
