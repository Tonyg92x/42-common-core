/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/02/24 14:02:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	push_back(t_llists *l, int len, int limit)
{
	int	size;

	size = len;
	while (size > 0)
	{
		if (l->start_b->position_wanted == l->count)
		{
			pa(l);
			ra(l, false);
			l->count++;
		}
		else if (l->start_b->position_wanted > limit)
			pa(l);
		else
			rb(l, false);
		size--;
	}
}

void	sort_first_quarter(t_llists *l, int quarter)
{
	push_back(l, l->len_b, quarter);
	while (l->len_b > 0 && l->start_a->position_wanted != quarter)
	{
		while (l->len_b > 12)
			push_med_b(l);
		sort_b(l);
		while (l->start_a->position_wanted <= quarter)
			rotate_sort(l);
	}
}

void	sort_second_quarter(t_llists *l, int median)
{
	while (l->start_a->position_wanted <= median)
		rotate_sort(l);
	while (l->len_b > 0 && l->start_a->position_wanted != median)
	{
		while (l->len_b > 12)
			push_med_b(l);
		sort_b(l);
		while (l->start_a->position_wanted <= median)
			rotate_sort(l);
	}
}

void	sort_third_quarter(t_llists *l, int quarter)
{
	push_back(l, l->len_b, quarter);
	while (l->len_b > 0 && l->start_a->position_wanted != quarter)
	{
		while (l->len_b > 12)
			push_med_b(l);
		sort_b(l);
		while (l->start_a->position_wanted <= quarter)
			rotate_sort(l);
	}
	while (l->start_a->position_wanted != 0)
		rotate_sort(l);
}

void	sort_last_quarter(t_llists *l)
{
	while (l->len_b > 0 || l->start_a->position_wanted != 0)
	{
		while (l->len_b > 12)
			push_med_b(l);
		sort_b(l);
		while (l->start_a->position_wanted != 0)
			rotate_sort(l);
	}
}
