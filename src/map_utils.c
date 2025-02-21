/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:10:37 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 13:12:04 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	find_longest_row_length(char **map) // szerokość z \n i \0 dla 1111 -> 6
{
	int		max_length;
	int		current_length;
	int		i;

	i = 0;
	max_length = 0;
	current_length = 0;
	while (map[i])
	{
		current_length = ft_strlen(map[i]);
		if (current_length > max_length)
		{
			max_length = current_length;
		}
		i++;
	}
	return (max_length);
}

// util do is_01SENW, sprawdza czy string kończy się znakiem nowej linii
int	ends_with_n(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[len - 1] == '\n')
		return (1);
	return (0);
}

// sprawdza czy w mapie są odpowiednie znaki, helper do validacji
int	is_01senw(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' &&
				map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' &&
				map[i][j] != ' ')
			{
				if (ends_with_n(map[i]) == 1 && j == ft_strlen(map[i]) - 1)
					break ;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
// Daje spacje żeby wyrównać długości rzędów do najdłuższego
char	*fill_spaces(char *line, int max_row_len)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc(sizeof(char) * (max_row_len + 1));
	while (line[i] && line[i] != 10)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < max_row_len)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

// dodaje spacje żeby wyrównać rzędy do najdłuższego, helper do validacji
char	**map_with_spaces(t_game game)
{
	int		i;
	int		max_row_len;
	char	**new_map;

	i = 0;
	max_row_len = find_longest_row_length(game.map.board);
	new_map = malloc(sizeof(char *) * (count_rows(game.map.file_path) + 1));
	while (game.map.board[i])
	{
		new_map[i] = fill_spaces(game.map.board[i], max_row_len);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}
