/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellini <mbellini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:00 by mbellini          #+#    #+#             */
/*   Updated: 2022/01/25 14:09:47 by mbellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_n(char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_save(char *save, char *buffer)
{
	char	*new_save;

	if (save == NULL && buffer[0] != '\0')
		new_save = ft_strdup(buffer);
	else
		new_save = ft_strjoin(save, buffer);
	free(save);
	if (!new_save)
		return (NULL);
	return (new_save);
}

char	*ft_line(int nread, char **save)
{
	char	*tmp;
	char	*ligne;

	ligne = NULL;
	if (find_n(*save) == -1 && nread == 0 && *save)
	{
		if (*save[0] != 0)
			ligne = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (ligne);
	}
	ligne = ft_substr(*save, 0, find_n(*save) + 1);
	if (!ligne)
		return (free(*save), NULL);
	tmp = ft_substr(*save, find_n(*save) + 1, BUFFER_SIZE + 1);
	free(*save);
	if (!tmp)
		return (NULL);
	*save = ft_strdup(tmp);
	free(tmp);
	if (!(*save))
		return (NULL);
	return (ligne);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*save = 0;
	int		nread;

	nread = 1;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (nread > 0 && find_n(save) == -1)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread < 0)
			return (NULL);
		buffer[nread] = '\0';
		save = ft_save(save, buffer);
		if (!(save))
			return (NULL);
	}
	return (ft_line(nread, &save));
}
  int main()
 {
 	int fd = open("big_line_with_nl", O_RDONLY);
 	if (fd == 2)
 		return (2);
 	char *s2;
 	while ((s2 = get_next_line(fd)) != NULL)
 	{
 		printf("%s", s2);
 		free(s2);
 	}
 	//get_next_line(fd);
 	//printf("%s", s2);
 }

//  int main(int argc, char **argv)
// {
//	(void) argc;
// 	int fd = open(argv[1], O_RDONLY);
// 	if (fd == 2)
// 		return (2);
// 	char *s2;
// 	while ((s2 = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", s2);
// 		free(s2);
// 	}
// 	//get_next_line(fd);
// 	//printf("%s", s2);
// }
