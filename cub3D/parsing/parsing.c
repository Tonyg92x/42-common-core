/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/09 16:18:47 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

char	*skip_empty_line(char *str)
{
	const char	*temp = ft_strtrim(str, " \n\t\v");

	if (ft_strlen(temp) == 0)
	{
		free((void *)temp);
		return (0);
	}
	else
		return ((char *)temp);
	return (NULL);
}

int	any_invalid(t_map *map)
{
	int	is_not_ok;

	is_not_ok = 0;
	if (map->west_texture == NULL)
		is_not_ok++;
	if (map->south_texture == NULL)
		is_not_ok++;
	if (map->est_texture == NULL)
		is_not_ok++;
	if (map->norh_texture == NULL)
		is_not_ok++;
	if (!map->floor_color || (map->floor_color && valid_range(
				map->floor_color)))
		is_not_ok++;
	if (!map->ceiling_color || (map->ceiling_color && valid_range(
				map->ceiling_color)))
		is_not_ok++;
	return (is_not_ok);
}

int	loop_directions(t_game *state)
{
	int	inc;
	int	status;

	status = 0;
	inc = 0;
	if (state->map != NULL)
	{
		while (state->map[inc])
		{
			ft_poll_texture(skip_empty_line(state->map[inc]),
				state->map_data, inc);
			ft_poll_color(skip_empty_line(state->map[inc]),
				state->map_data, inc);
			inc++;
		}
		if (any_invalid(state->map_data))
			return (printf("texture or color resulted in error\n"));
	}
	else
	{
		ft_putstr_fd("could not readfile\n", 2);
		return (1);
	}
	state->map_data->iterator++;
	return (status);
}
