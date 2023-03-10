/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/09 13:13:15 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stddef.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>

typedef struct linked_list
{
	struct linked_list	*next;
	struct linked_list	*prev;
	int					position_wanted;
	int					content;
}					t_llist;

typedef struct linked_lists
{
	struct linked_list	*start_a;
	struct linked_list	*start_b;
	int					len_a;
	int					len_b;
	int					count;
	int					option;
}					t_llists;

// Linked list fonctions
int			argv_size(char **argv);
bool		lim_test(char **argv, t_llists *l);
bool		check_digit(char **argv, t_llists *l);
bool		check_doublons(char **argv, t_llists *l);
t_llist		*init_list(char **argv, t_llists *l);
void		print_lists(t_llists *l);
void		ft_free_lists(t_llists *l);

// Push_swap functions
void		sa(t_llists *l, bool ss);
void		sb(t_llists *l, bool ss);
void		ss(t_llists *l);
void		pa(t_llists *l);
void		pb(t_llists *l);
void		ra(t_llists *l, bool rr);
void		rb(t_llists *l, bool rr);
void		rr(t_llists *l);
void		rra(t_llists *l, bool rrr);
void		rrb(t_llists *l, bool rrr);
void		rrr(t_llists *l);

// libft addons
long int	ft_atol(char *string);
int			smallest(int *tab, int *len);
void		ft_free2d(char **string);

// algo fonctions
void		sort_ll(t_llists *l);
void		init_option(t_llists *l);
int			biggest_list(t_llists *l);
void		init_pos_wanted(t_llists *l);
bool		sorted(t_llists *l);
bool		sorted_a(t_llists *l);
bool		sorted_b(t_llists *l);
bool		smallest_pos_wanted(t_llist *l);
bool		biggest_pos_wanted(t_llist *l);
int			get_median(t_llist *l, int size);
void		push_med_b(t_llists *l);
void		sort_b(t_llists	*l);
void		first_push(t_llists *l);
int			smal_pos(t_llist *l, int *plancher);
void		push_back(t_llists *l, int len, int limit);
void		sort_first_quarter(t_llists *l, int quarter);
void		sort_second_quarter(t_llists *l, int median);
void		sort_third_quarter(t_llists *l, int quarter);
void		sort_last_quarter(t_llists *l);
void		rotate_sort(t_llists *l);
void		sort_under_100(t_llists *l);

#endif
