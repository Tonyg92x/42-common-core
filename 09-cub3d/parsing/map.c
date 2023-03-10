/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/09 15:25:34 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Include/cube.h" 

int	parse_location(t_game *game, int found, int inc)
{
	int	temp;

	temp = game->map_data->start;
	while (game->map[temp] && !only_space(game->map[temp]))
	{
		found += parser_helper(game, temp, inc);
		temp++;
		inc++;
	}
	if (found > 1)
		return (1);
	temp = game->map_data->start;
	while (game->map[temp] && !only_space(game->map[temp]))
	{
		if (was_in_set(game->map[temp], "01NEWS ") != 0)
		{
			printf("wrong element in field\n");
			return (1);
		}
		temp++;
	}
	if (found == 0)
		return (1);
	return (0);
}

int	parsing(t_game *game, int temp)
{
	if (loop_directions(game))
		return (1);
	while (game->map[game->map_data->iterator + 1] && only_space(game->map[
				game->map_data->iterator]))
		game->map_data->iterator++;
	temp = game->map_data->iterator;
	game->map_data->start = temp;
	if (ft_all(game->map[temp], '1'))
		return (assert(1, "all  are not one\n"));
	while (game->map[temp])
	{
		if (only_space(game->map[temp]))
			return (ft_all(game->map[temp - 1], '1'));
		if (any_one_above_line(game, temp))
			return (assert(1, "above\n"));
		if (ft_between(game->map[temp], '1') != 0)
			return (assert(1, "the wall on the left or right are not '1' \n"));
		if (any_one_bellow_line(game->map, temp++))
			return (1);
	}
	return (0);
}

int	first_seen(char *str)
{
	int		inc;
	char	*temp;

	inc = 0;
	temp = ft_strchr(str, ' ');
	while (temp[inc] == ' ')
		inc++;
	if (temp[inc] == '1')
		return (0);
	return (1);
}

int	verif_no_space(t_game *game, int pos)
{
	int	iter;
	int	temp;

	iter = pos;
	temp = 0;
	while (!skip_empty_line(game->map[iter]))
		iter++;
	if (ft_all(game->map[iter], '1'))
		return (1);
	if (ft_until_this(game->map[iter], " ") != -1)
	{
		temp = ft_until_this(game->map[iter], " ");
		if (temp > last_seen_at(game->map[iter], '1'))
			return (0);
		if (first_seen(game->map[iter]) || game->map[iter][temp - 1] != '1')
			return (1);
	}
	return (0);
}

int	any_one_above(t_game *map, int current_line, int pos)
{
	while (current_line > map->map_data->iterator)
	{
		current_line--;
		if (map->map[current_line] && pos <= (int)
			ft_strlen(map->map[current_line]))
		{
			if (map->map[current_line][pos] == '1')
				return (0);
			else if (map->map[current_line][pos] == ' ')
				return (1);
			else
				continue ;
		}
		if (pos > (int)ft_strlen(map->map[current_line]))
			return (1);
		else if (map->map[current_line + 1][pos] == '1')
			return (0);
	}
	return (0);
}
