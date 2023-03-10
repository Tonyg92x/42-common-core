/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/21 14:33:08 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

//	For every string entered as arguments, fill a linked list of 
//	it's command and arguments if there is some.
void	initialise_command_list(t_command_list *l, int argc, char **argv)
{
	int			i;
	t_command	*temp;

	l->start = malloc(sizeof(t_command));
	l->start->prev = NULL;
	l->start->cmd = ft_split(argv[2], ' ');
	l->len = 1;
	temp = l->start;
	i = 3;
	while (i < argc - 1)
	{
		temp->next = malloc(sizeof(t_command));
		temp->next->prev = temp;
		temp = temp->next;
		temp->cmd = ft_split(argv[i], ' ');
		l->len++;
		i++;
	}
}

//	Free all memory allocated in the command list.
void	free_command_list(t_command_list *l)
{
	t_command	*temp;
	t_command	*temp2;

	if (l->start != NULL)
	{
		temp = l->start;
		while (temp != NULL)
		{
			if (temp->cmd != NULL)
				ft_free2d(temp->cmd);
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
	}
	free(l);
}
