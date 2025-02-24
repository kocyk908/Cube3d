/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/24 22:38:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// zlicza ilość wierszy w mapie, helper do validacji mapy
int	count_rows(char *file_path)
{
	int		fd;
	int		row_count;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	row_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		row_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (row_count);
}

// odczytuje GNLinem plik .cub, i zapisuje do char **map
char	**read_file(char *file_path)
{
	int		fd;
	int		added_row;
	char	**file;
	char	*line;

	added_row = 0;
	if (count_rows(file_path) < 0)
		return (NULL);
	file = malloc(sizeof(char *) * (count_rows(file_path) + 1));
	if (!file)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		file[added_row] = ft_strdup(line);
		free(line);
		if (!file[added_row++])
			return (free_map(file), close(fd), NULL);
		line = get_next_line(fd);
	}
	file[added_row] = NULL;
	return (close(fd), file);
}

void	init_read_map(int fd, int *added_row, char ***file, t_game *game)
{
	*added_row = 0;
	*file = malloc(sizeof(char *)
			* (count_rows((*game).map.file_path)
				- (*game).textures.height_util + 1));
	if (!*file)
		return ;
	while ((*game).textures.height_util--)
		free(get_next_line(fd));
}

char	**read_map(t_game *game)
{
	int		fd;
	int		added_row;
	char	**file;
	char	*line;

	if (count_rows(game->map.file_path) < 0)
		return (NULL);
	fd = open(game->map.file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	init_read_map(fd, &added_row, &file, game);
	if (!file)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line)
	{
		file[added_row++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	file[added_row] = NULL;
	game->map.height = added_row;
	return (trim_empty_lines(file, added_row));
}

// Usuwa puste linie na końcu
char	**trim_empty_lines(char **file, int added_row)
{
	while (added_row > 0 && (file[added_row - 1][0] == '\n'
		|| file[added_row - 1][0] == '\0'))
	{
		free(file[added_row - 1]);
		file[added_row - 1] = NULL;
		added_row--;
	}
	return (file);
}
