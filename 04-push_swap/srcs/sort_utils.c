/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/02/24 13:56:34 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//	Return true if the list start entered has
//	the smallest pos wanted in the list.
bool	smallest_pos_wanted(t_llist *l)
{
	int	i;

	i = l->position_wanted;
	while (l->prev != NULL)
		l = l->prev;
	while (l)
	{
		if (l->position_wanted < i)
			return (false);
		l = l->next;
	}
	return (true);
}

//	Return true if the list start entered has
//	the biggest pos wanted in the list.
bool	biggest_pos_wanted(t_llist *l)
{
	int	i;

	i = l->position_wanted;
	while (l->prev != NULL)
		l = l->prev;
	while (l)
	{
		if (l->position_wanted > i)
			return (false);
		l = l->next;
	}
	return (true);
}

//	Return the smallest position wanted in
//	the list that is bigger then plancher
int	smal_pos(t_llist *l, int *plancher)
{
	t_llist	*temp;
	int		retour;

	retour = 2147483647;
	temp = l;
	while (temp)
	{
		if (temp->position_wanted < retour
			&& temp->position_wanted > (*plancher))
			retour = temp->position_wanted;
		temp = temp->next;
	}
	(*plancher) = retour;
	return (retour);
}

//	Get in the start of a list with his size.
//	get out the median of the pos wanted.
int	get_median(t_llist *l, int size)
{
	int		tab[1000000];
	int		i;
	int		plancher;

	plancher = -2147483648;
	i = 0;
	while (i < size)
		tab[i++] = smal_pos(l, &plancher);
	return (tab[size / 2]);
}

//	Push the every element smaller than median
void	first_push(t_llists *l)
{
	int	median;
	int	size;

	size = l->len_a;
	median = get_median(l->start_a, l->len_a);
	while (size > 0)
	{
		if (l->start_a->position_wanted < median)
			pb(l);
		else if (l->len_b > 1 && l->start_b->position_wanted
			> l->start_b->next->content)
			rr(l);
		else
			ra(l, false);
		size--;
	}
}
