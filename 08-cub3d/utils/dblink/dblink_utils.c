/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dblink_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemartel <jemartel@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:07:53 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/06 12:54:46 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/cube.h"
#include "stdlib.h"

t_dlist	*ft_lst_lastnode(t_dlist *currlist)
{
	while (currlist->next)
	{
		if (!currlist->next)
			return (currlist);
		currlist = currlist->next;
	}
	return (currlist);
}

t_dlist	*ft_lst_firstnode(t_dlist *currlist)
{
	while (currlist)
	{
		if (!currlist->prev)
			return (currlist);
		currlist = currlist->prev;
	}
	return (currlist);
}

t_dlist	*ft_lst_nextnode(t_dlist *currlist)
{
	currlist = currlist->next;
	return (currlist);
}

int	ft_lst_lenght(t_dlist *currlist)
{
	int	len;

	len = 0;
	while (currlist)
	{
		currlist = currlist->next;
		len++;
	}
	return (len);
}

t_dlist	*ft_lstnewl(void *content)
{
	t_dlist	*link;

	link = (t_dlist *)malloc(sizeof(*link));
	if (!link)
		return (NULL);
	link->content = content;
	link->next = NULL;
	return (link);
}
