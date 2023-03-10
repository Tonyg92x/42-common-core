/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/02/24 11:09:02 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//	Return true if the list a is sorted
bool	sorted_a(t_llists *l)
{
	t_llist	*temp;

	temp = l->start_a;
	if (l->start_a != NULL && l->start_a->next != NULL)
	{
		while (temp->next != NULL)
		{
			if (temp->position_wanted > temp->next->position_wanted)
				return (false);
			temp = temp->next;
		}
	}
	return (true);
}

//	Return true if the list b is sorted
bool	sorted_b(t_llists *l)
{
	t_llist	*temp;

	temp = l->start_b;
	if (l->start_b != NULL && l->start_b->next != NULL)
	{
		while (temp->next != NULL)
		{
			if (temp->position_wanted < temp->next->position_wanted)
				return (false);
			temp = temp->next;
		}
	}
	return (true);
}

//	Return true if both list are sorted
bool	sorted(t_llists *l)
{
	if (sorted_a(l) == false)
		return (false);
	if (sorted_b(l) == false)
		return (false);
	return (true);
}

//	Push half of the biggest element to a
void	push_med_b(t_llists *l)
{
	int	median;
	int	size;

	median = get_median(l->start_b, l->len_b);
	size = l->len_b;
	while (size > 0)
	{
		if (l->start_b->position_wanted == l->count)
		{
			pa(l);
			ra(l, false);
			l->count++;
		}
		else if (l->start_b->position_wanted > median)
		{
			pa(l);
		}
		else
			rb(l, false);
		size--;
	}
}

void	sort_b(t_llists	*l)
{
	while (l->len_b > 0)
	{
		if (l->start_b->position_wanted == l->count)
		{
			pa(l);
			l->count++;
			if (l->len_b > 0 && l->start_b->position_wanted != l->count)
				rr(l);
			else
				ra(l, false);
		}
		else
			rb(l, false);
	}
}
