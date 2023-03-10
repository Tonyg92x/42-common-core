/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/15 09:15:24 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

// Fonction wich look in the list if any value is not in int limit.
bool	lim_test(char **argv, t_llists *l)
{
	int			i;
	long int	content;
	int			size;

	size = argv_size(argv);
	i = 0;
	while (size > 0)
	{
		content = ft_atol(argv[i]);
		if (content > 2147483647 || content < -2147483648)
		{
			ft_printf("Error\n");
			ft_free_lists(l);
			return (true);
		}
		i++;
		size--;
	}
	return (false);
}

// Comparer every element to look for "doulons"
static bool	compare_elements(int *content, int size)
{
	int	y;
	int	i;

	i = 0;
	while (i < size)
	{
		y = i + 1;
		while (y < size)
		{
			if (content[i] == content[y])
			{
				ft_printf("Error\n");
				return (true);
			}
			y++;
		}
		i++;
	}
	return (false);
}

//	Fonction that return true if any arguments in
//	argv are identical.
bool	check_doublons(char **argv, t_llists *l)
{
	int		i;
	int		*content;
	int		size;

	size = argv_size(argv);
	content = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		content[i] = ft_atoi(argv[i]);
		i++;
	}
	if (compare_elements(content, size))
	{
		free(content);
		ft_free_lists(l);
		return (true);
	}
	free(content);
	return (false);
}

//	Put every element of the string list in a linked list.
//	PS : Don't forget to free the memory.
t_llist	*init_list(char **argv, t_llists *l)
{
	int		i;
	t_llist	*start_a;
	t_llist	*temp;

	if (lim_test(argv, l))
		return (NULL);
	if (check_doublons(argv, l))
		return (NULL);
	if (check_digit(argv, l))
		return (NULL);
	start_a = malloc(sizeof(t_llist));
	start_a->content = ft_atoi(argv[0]);
	start_a->position_wanted = 0;
	i = 1;
	temp = start_a;
	while (argv[i] != NULL && argv_size(argv) > i - 1)
	{
		temp->next = malloc(sizeof(t_llist));
		temp->next->prev = temp;
		temp->next->content = ft_atoi(argv[i]);
		temp = temp->next;
		l->len_a++;
		i++;
	}
	return (start_a);
}

// Populate data on the list to organise sorting
void	init_option(t_llists *l)
{
	l->count = 0;
	if (l->len_a == 2)
		l->option = 2;
	else if (l->len_a == 3)
		l->option = 3;
	else if (l->len_a == 5)
		l->option = 5;
	else if (l->len_a < 90)
		l->option = 100;
}
