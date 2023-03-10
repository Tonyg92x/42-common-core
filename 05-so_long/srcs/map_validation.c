/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:35:51 by aguay             #+#    #+#             */
/*   Updated: 2022/03/28 15:18:16 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static bool	is_dot_ber(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] == 'r' && file[i - 2] == 'e'
		&& file[i - 3] == 'b' && file[i - 4] == '.')
		return (true);
	return (false);
}

static bool	main_loop3(char *str, int *i, int *e, int *c)
{
	if (str[(*i)] == '0' || str[(*i)] == '1' || str[(*i)] == 'C'
		|| str[(*i)] == 'E' || str[(*i)] == 'P')
	{
		if (str[(*i)] == 'E')
			(*e)++;
		else if (str[(*i)] == 'P')
			(*c)++;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

static bool	main_loop2(int fd, size_t size, char *str)
{
	int	i;
	int	e;
	int	c;

	e = 0;
	c = 0;
	while (str != NULL)
	{
		if (size != ft_strlen(str))
			return (quit(fd, str));
		if (str[0] != '1' || str[size - 1] != '1')
			return (quit(fd, str));
		i = 0;
		while (str[i])
		{
			if (main_loop3(str, &i, &e, &c) == false)
				return (quit(fd, str));
		}
		str = next_str(str, fd);
	}
	if (e != 1 || c != 1)
		return (quit(fd, str));
	return (true);
}

static bool	main_loop(int fd)
{
	char	*str;
	size_t	size;
	int		c;

	c = 0;
	str = next_str(NULL, fd);
	while (str[c])
	{
		if (str[c++] != '1')
			return (quit(fd, str));
	}
	size = ft_strlen(str);
	if (size > 100)
		return (quit(fd, str));
	if (main_loop2(fd, size, str) == false)
		return (false);
	return (true);
}

bool	validate_map(char	*file)
{
	int			fd;
	char		*file_trim;

	fd = 0;
	file_trim = ft_strtrim(file, " ");
	if (is_dot_ber(file) == false)
		return (quit(fd, file_trim));
	fd = open(file_trim, O_RDONLY);
	if (fd == -1)
		return (quit(fd, file_trim));
	if (main_loop(fd) == false)
		return (quit(fd, file_trim));
	close(fd);
	free(file_trim);
	return (true);
}
