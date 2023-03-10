/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/09 13:12:31 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

// Get the number of strings in a string list
int	argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

bool	check_digit(char **argv, t_llists *l)
{
	int	i;
	int	y;
	int	size;

	size = argv_size(argv);
	i = 0;
	while (i < size)
	{
		y = 0;
		while (argv[i][y])
		{
			if (isdigit(argv[i][y]) == false && argv[i][y] != ' ' &&
			argv[i][y] != '-')
			{
				ft_printf("Error\n");
				ft_free_lists(l);
				return (true);
			}
			y++;
		}
		i++;
	}
	return (false);
}

void	ft_free_lists(t_llists *l)
{
	t_llist	*temp;

	if (l->start_a != NULL)
	{
		while (l->start_a->next != NULL)
		{
			temp = l->start_a->next;
			free(l->start_a);
			l->start_a = temp;
		}
		free(l->start_a);
	}
	if (l->start_b != NULL)
	{
		while (l->start_b->next != NULL)
		{
			temp = l->start_b->next;
			free(l->start_b);
			l->start_b = temp;
		}
		free(l->start_b);
	}
	free(l);
}
