/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-phil <jemartel@student.42quebec>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 10:22:02 by jean-phil         #+#    #+#             */
/*   Updated: 2022/06/06 12:52:50 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>

static char	*findme(char *str, char *location)
{
	int		inc;
	int		cin;
	char	*found;

	found = NULL;
	inc = 0;
	cin = 0;
	if (!str)
		return (NULL);
	while (str[inc] != *location)
		inc++;
	found = malloc(sizeof(char) * inc + 1);
	if (!found)
		return (NULL);
	while (cin != inc)
	{
		found[cin] = str[cin];
		cin++;
	}
	found[inc] = '\0';
	return (found);
}

static int	readme(int fd, char *buffer, int *val)
{
	*val = read(fd, buffer, BUFFSIZE);
	buffer[*val] = '\0';
	return (*val);
}

static char	*ft_output2(char *container, char **line)
{
	char	*found;

	found = NULL;
	found = ft_strchrr(container, '\n');
	if (found)
	{
		*line = findme(container, found);
		found = ft_strdup(found + 1);
		free(container);
		if (ft_strlen(found) == 0)
		{
			free(found);
			return (NULL);
		}
		return (found);
	}
	return (NULL);
}

char	*outlast(char *container, char **line)
{
	if (container)
	{
		*line = ft_strdup(container);
		free(container);
		container = NULL;
	}
	else
		*line = NULL;
	return (container);
}

int	get_next_line(int fd, char **line)
{
	static char	*container;
	char		buff[BUFFSIZE];
	int			val;

	if (fd < 0 || !line || BUFFSIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (ft_strchrr(container, '\n'))
	{
		container = ft_output2(container, line);
		return (1);
	}
	while (readme(fd, buff, &val) > 0)
	{
		container = ft_strjoin(container, buff);
		if (ft_strchrr(container, '\n'))
		{
			container = ft_output2(container, line);
			return (1);
		}
	}
	container = outlast(container, line);
	return (0);
}
