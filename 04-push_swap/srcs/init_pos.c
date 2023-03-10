/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/09 13:15:31 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//	Return the smallest value of the list a
long int	smallest_value(t_llists *l, long int *plancher)
{
	t_llist		*p;
	long int	retour;

	p = l->start_a;
	retour = 2147483647;
	while (p)
	{
		if (p->content < retour && p->content > (*plancher))
		{
			retour = p->content;
		}
		p = p->next;
	}
	(*plancher) = retour;
	return (retour);
}

//	Class every element in the wanted order
long int	*class_table(t_llists *l)
{
	long int	*tab;
	int			size;
	int			i;
	long int	plancher;

	plancher = -2147483649;
	size = l->len_a;
	tab = malloc(sizeof(long int) * l->len_a);
	i = 0;
	while (size > 0)
	{
		tab[i] = smallest_value(l, &plancher);
		i++;
		size--;
	}
	return (tab);
}

//	Put the wanted position to every elements
void	fill_wanted_pos(t_llists *l, long int *tab)
{
	int		i;
	t_llist	*temp;

	i = 0;
	while (i < l->len_a)
	{
		temp = l->start_a;
		while (true)
		{
			if (tab[i] == temp->content)
			{
				temp->position_wanted = i;
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
	return ;
}

// Get the value of the median
void	init_pos_wanted(t_llists *l)
{
	long int	*tab;

	tab = class_table(l);
	fill_wanted_pos(l, tab);
	free(tab);
}
