/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:25:02 by aguay             #+#    #+#             */
/*   Updated: 2022/03/16 08:47:12 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static bool	only_digit(char **argv, int argc)
{
	int	i;
	int	y;

	i = 1;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y])
		{
			if (ft_isdigit(argv[i][y]) == 0 &&
				argv[i][y] != ' ' && argv[i][y] != '-')
			{
				ft_printf("Error\n");
				return (false);
			}
			y++;
		}
		i++;
	}
	return (true);
}

static char	**initiate_argv(char **argv, int argc, t_llists *l)
{
	char	**retour;
	int		i;

	if (only_digit(argv, argc) == false)
		return (NULL);
	i = 0;
	l->len_a = 1;
	l->len_b = 0;
	l->start_b = NULL;
	if (argc == 2)
	{
		retour = ft_split(argv[1], ' ');
		if (retour[1] == NULL)
		{
			free(retour[0]);
			if (retour)
				free(retour);
			return (NULL);
		}
		return (retour);
	}
	return (&argv[1]);
}

int	main(int argc, char **argv)
{
	t_llists	*l;

	if (argc <= 1)
		return (0);
	l = malloc(sizeof(t_llists));
	if (!l)
		return (0);
	argv = initiate_argv(argv, argc, l);
	if (argv == NULL)
	{
		ft_free_lists(l);
		return (0);
	}
	l->start_a = init_list(argv, l);
	if (l->start_a != NULL)
	{
		init_pos_wanted(l);
		init_option(l);
		sort_ll(l);
		ft_free_lists(l);
	}
	if (argc == 2)
		ft_free2d(argv);
	return (0);
}
