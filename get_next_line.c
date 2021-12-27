/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellini <mbellini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:00 by mbellini          #+#    #+#             */
/*   Updated: 2021/12/27 16:36:56 by mbellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *save, char *buffer)
{
	char	*line;

	if (!save)
	{
		save = ft_substr(buffer, find_n(buffer) + 1, BUFFER_SIZE - find_n(buffer));
		printf("!save: %s\n", save);
		line = ft_substr(buffer, 0, find_n(buffer) + 1);
	}
	else
	{
		line = ft_strjoin(save, ft_substr(buffer, 0, find_n(buffer) + 1));
		free(save);
		save = ft_substr(buffer, find_n(buffer) + 1, BUFFER_SIZE - find_n(buffer));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1];
	static char *save = NULL;
	//printf("save: %s\n", save);
	ssize_t	nread;

	nread = 1;
	while (nread != 0 && find_n(save) == -1)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		buffer[nread] = '\0';
		if (find_n(buffer) != -1)
		{
			printf("gnl save: %s\n", save);
			return (next_line(save, buffer));
		}
		else
			save = ft_substr(buffer, 0, BUFFER_SIZE);
	}
	return (NULL);
}

int main()
{
	int fd = open("test", O_RDONLY);
	if (fd == 0)
		return (0);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
}
