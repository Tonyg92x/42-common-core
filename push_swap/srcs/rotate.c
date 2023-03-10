/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/09 09:23:11 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	sort_under_100(t_llists *l)
{
	while (l->start_a != NULL)
	{
		if (l->start_a->position_wanted == l->count)
		{
			l->count++;
			pb(l);
		}
		else
			ra(l, false);
	}
	while (l->start_b != NULL)
		pa(l);
}

// Rotate every element by one to the top.
// Element 0 go under the stack.
void	ra(t_llists *l, bool rr)
{
	t_llist	*temp;
	t_llist	*temp2;

	if (l->len_a < 2)
		return ;
	temp = l->start_a;
	l->start_a->next->prev = NULL;
	l->start_a = l->start_a->next;
	temp2 = l->start_a;
	while (temp2->next != NULL)
		temp2 = temp2->next;
	temp2->next = temp;
	temp->prev = temp2;
	temp->next = NULL;
	if (rr == false)
		ft_printf("ra\n");
}

// Rotate every element by one to the top.
// Element 0 go under the stack.
void	rb(t_llists *l, bool rr)
{
	t_llist	*temp;
	t_llist	*temp2;

	if (l->len_b < 2)
		return ;
	temp = l->start_b;
	l->start_b->next->prev = NULL;
	l->start_b = l->start_b->next;
	temp2 = l->start_b;
	while (temp2->next != NULL)
		temp2 = temp2->next;
	temp2->next = temp;
	temp->prev = temp2;
	temp->next = NULL;
	if (rr == false)
		ft_printf("rb\n");
}

void	rr(t_llists *l)
{
	ra(l, true);
	rb(l, true);
	ft_printf("rr\n");
}
