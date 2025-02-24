/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:08:14 by lkoc              #+#    #+#             */
/*   Updated: 2024/03/19 10:08:18 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != (char)c)
	{
		i++;
	}
	if (s[i] == (char)c)
	{
		return ((char *)&s[i]);
	}
	return ((char *) NULL);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (2147483647 / nmemb < size)
		return (NULL);
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	while (i < size * nmemb)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

char	*ft_join_iterate(char *str, char *s1, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (buff[j])
	{
		str[i + j] = buff[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *buff)
{
	char	*str;
	int		len;

	len = ft_strlen_gnl(s1) + ft_strlen_gnl(buff);
	if (!buff)
		return (NULL);
	if (!s1)
	{
		s1 = (char *)ft_calloc_gnl(sizeof(char), 1);
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str = ft_join_iterate(str, s1, buff);
	free(s1);
	return (str);
}
