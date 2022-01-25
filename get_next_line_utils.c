/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellini <mbellini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:28:19 by mbellini          #+#    #+#             */
/*   Updated: 2022/01/25 14:49:57 by mbellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	while (start < slen && s[start + i] && i < len)
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (start < slen && i < len && s[i])
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;
	int		slen;

	slen = 0;
	i = 0;
	while (s[slen])
		slen++;
	cpy = malloc(sizeof(char) * (slen + 1));
	if (!cpy)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static char	*ft_cpy(char *res, const char *s1, const char *s2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	reslen;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	reslen = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (reslen + 1));
	if (!result)
		return (NULL);
	return (ft_cpy(result, s1, s2));
}
