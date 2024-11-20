/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:08:31 by lkoc              #+#    #+#             */
/*   Updated: 2024/03/21 12:08:35 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_readed_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	while (str[j] != '\0' && str[j] != '\n')
	{
		line[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static void	set_variables(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

static char	*ft_move_start(char *str)
{
	char	*new_buff;
	int		i;
	int		j;

	set_variables(&i, &j);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '\n')
		i++;
	new_buff = (char *)malloc(ft_strlen_gnl(str) - i + 1);
	if (!new_buff)
		return (NULL);
	while (str[i + j] != '\0')
	{
		new_buff[j] = str[i + j];
		j++;
	}
	new_buff[j] = '\0';
	free(str);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	int			fd_read;
	static char	*read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_read = 1;
	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!(ft_strchr_gnl(read_line, '\n')) && fd_read != 0)
	{
		fd_read = read(fd, tmp, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[fd_read] = '\0';
		read_line = ft_strjoin_gnl(read_line, tmp);
	}
	free(tmp);
	tmp = ft_readed_line(read_line);
	read_line = ft_move_start(read_line);
	return (tmp);
}