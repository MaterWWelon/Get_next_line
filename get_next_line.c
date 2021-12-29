/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellini <mbellini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:00 by mbellini          #+#    #+#             */
/*   Updated: 2021/12/29 15:23:14 by mbellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char **save, char *buffer)
{
	char	*line;

	if (!*save)
	{
		*save = ft_substr(buffer, find_n(buffer) + 1,
				BUFFER_SIZE - find_n(buffer));
		line = ft_substr(buffer, 0, find_n(buffer) + 1);
	}
	else
	{
		line = ft_strjoin(*save, ft_substr(buffer, 0, find_n(buffer) + 1));
		free(*save);
		*save = ft_substr(buffer, find_n(buffer) + 1,
				BUFFER_SIZE - find_n(buffer));
	}
	return (line);
}

void	ft_save(char **save, char *buffer)
{
	if (*save)
		*save = ft_strjoin(*save, buffer);
	else
		*save = ft_substr(buffer, 0, BUFFER_SIZE);
}

char	*find_n_save(char **save)
{
	char	*line;

	line = ft_substr(*save, 0, find_n(*save) + 1);
	*save = ft_substr(*save, find_n(*save) + 1, BUFFER_SIZE - find_n(*save));
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*save;
	ssize_t		nread;

	nread = 1;
	while (nread != 0 && find_n(save) == -1)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		buffer[nread] = '\0';
		if (find_n(buffer) != -1)
		{
			return (next_line(&save, buffer));
		}
		else
			ft_save(&save, buffer);
	}
	if (find_n(save) != -1)
		return (find_n_save(&save));
	return (NULL);
}

/* int main()
{
	int fd = open("test", O_RDONLY);
	if (fd == 1)
		return (1);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
}
 */