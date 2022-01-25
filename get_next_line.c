/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellini <mbellini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:00 by mbellini          #+#    #+#             */
/*   Updated: 2022/01/25 14:47:27 by mbellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_n(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*add_mem(char *lu_init, char *buff)
{
	char	*new_lu;

	if (lu_init == NULL && buff[0] != '\0')
		new_lu = ft_strdup(buff);
	else
		new_lu = ft_strjoin(lu_init, buff);
	free(buff);
	free(lu_init);
	if (!new_lu)
		return (NULL);
	return (new_lu);
}

char	*get_line(int n_read, char **lu)
{
	char	*tmp;
	char	*ligne;

	ligne = NULL;
	if (find_n(*lu) == -1 && n_read == 0 && *lu)
	{
		if (*lu[0] != 0)
			ligne = ft_strdup(*lu);
		free(*lu);
		*lu = NULL;
		return (ligne);
	}
	ligne = ft_substr(*lu, 0, find_n(*lu) + 1);
	if (!ligne)
		return (free(*lu), NULL);
	tmp = ft_substr(*lu, find_n(*lu) + 1, BUFFER_SIZE + 1);
	free(*lu);
	if (!tmp)
		return (NULL);
	*lu = ft_strdup(tmp);
	free(tmp);
	if (!(*lu))
		return (NULL);
	return (ligne);
}

char	*get_next_line(int fd)
{
	static char		*lu = 0;
	char			*buff;
	int				n_read;

	n_read = 1;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (find_n(lu) == -1 && n_read > 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		n_read = read(fd, buff, BUFFER_SIZE);
		if (n_read < 0)
			return (free(buff), NULL);
		buff[n_read] = '\0';
		lu = add_mem(lu, buff);
		if (!(lu))
			return (NULL);
	}
	return (get_line(n_read, &lu));
}
