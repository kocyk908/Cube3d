/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 13:35:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


// szuka długości najdłuższego wiersza w mapie, helper do validacji, do map_with_spaces

int find_longest_row_length(char **map) // szerokość z \n i \0 dla 1111 -> 6
{
    int max_length = 0;
    int current_length;
    int i = 0;

    while (map[i])
    {
        current_length = ft_strlen(map[i]);
        if (current_length > max_length)
        {
            max_length = current_length;
        }
        i++;
    }
    return max_length;
}


// util do is_01SENW, sprawdza czy string kończy się znakiem nowej linii
int ends_with_n(char *str)
{
    int len;
    
    len = ft_strlen(str);
    if (len < 2)
        return (0);
    if (str[len - 1] == '\n')
        return (1);
    return (0);
}

// sprawdza czy w mapie są odpowiednie znaki, helper do validacji
int is_01SENW(char **map)
{
    size_t i;
    size_t j;

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
                    break;
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

// zlicza ilość wierszy w mapie, helper do validacji mapy
int count_rows(char *file_path)
{
    int fd;
    int row_count;
    char *line;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (-1);
    }
    row_count = 0;
    while ((line = get_next_line(fd)))
    {
        row_count++;
        free(line);
    }
    close(fd);
    return (row_count);
}

// odczytuje GNLinem plik .cub, i zapisuje do char **map
char **read_file(char *file_path)
{
    int     fd;
    int     added_row;
    char    **file;
    char    *line;

    added_row = 0;
    file = NULL;
    if (count_rows(file_path) < 0)
        return (NULL);
    line = NULL;

    file = malloc(sizeof(char *) * (count_rows(file_path) + 1));
	fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (NULL);
    }
    while ((line = get_next_line(fd)))
    {
        file[added_row++] = ft_strdup(line);
        free(line);
    }

    close(fd);
    file[added_row] = NULL;

    return (file);
}

char **read_map(t_game *game)
{
    int     fd;
    int     added_row;
    char    **file;
    char    *line;
    int    i;

    i = 0;
    added_row = 0;
    file = NULL;
    line = NULL;
    file = malloc(sizeof(char *) * ((count_rows(game->map.file_path) - game->textures.height_util)  + 1));
	fd = open(game->map.file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (NULL);
    }
    while ((line = get_next_line(fd)))
    {
        if (i < game->textures.height_util)
        {
            i++;
            free(line);
            continue;
        }
        file[added_row++] = ft_strdup(line);
        free(line);
    }
    close(fd);

    while (added_row > 0 && (file[added_row - 1][0] == '\n' || file[added_row - 1][0] == '\0'))
    {
        free(file[added_row - 1]);
        file[added_row - 1] = NULL;
        added_row--;
    }

    game->textures.height_util = added_row;
    // Ensure null-termination
    file[added_row] = NULL;

    return (file);
}


// Funkcja do validacji, daje spacje żeby wyrównać długości rzędów do najdłuższego
char *fill_spaces(char *line, int max_row_len)
{
    char *new_line;
    int i;

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
char **map_with_spaces(t_game game)
{
    int i;
    int max_row_len;
    char **new_map;

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

// Funkcja do zwolnienia pamięci mapy
void free_map(char **map)
{
	int i;

	i = 0;
    if (!map)
        return ;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}