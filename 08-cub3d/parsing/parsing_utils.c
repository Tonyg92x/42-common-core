/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:00:47 by jemartel          #+#    #+#             */
/*   Updated: 2022/05/29 08:14:12 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/cube.h"

int	verif_number(char **strs)
{
	int	inc;
	int	cin;

	cin = 0;
	inc = 0;
	while (strs[inc])
	{
		while (strs[inc][cin])
		{
			if (ft_isdigit(strs[inc][cin]))
				cin++;
			else
				return (1);
		}
		cin = 0;
		inc++;
	}
	return (0);
}

int	valid_range(int *numbers)
{
	int	is_not_ok;
	int	inc;

	inc = 0;
	is_not_ok = 0;
	while (inc < 4)
	{
		if (numbers[inc] < 0 || numbers[inc] > 255)
		{
			is_not_ok = 1;
			break ;
		}
			inc++;
	}
	return (is_not_ok);
}
