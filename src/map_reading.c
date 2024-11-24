#include "game.h"


// szuka długości najdłuższego wiersza w mapie, helper do validacji, do map_with_spaces
int find_longest_row_length(char **map)
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



// sprawdzanie czy mapy jest okej, do read_map
// pomija znaki \n i \r jeśli na końcu

// sprawdza tez czy wiersze są długie przynajmniej 5 znaków, ale to trzeba poprawić raczej
int is_01SENW(char **map)
{
    size_t i;
    size_t j;

	i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' &&
                map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != ' ')
            {
			    if (ft_strlen(map[i]) < 5)
			    {
				    return (0);
			    }
			    if (j == ft_strlen(map[i]) - 2 && map[i][j] == 13 && map[i][j + 1] == 10)
				    return (1);
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

// odczytuje GNLinem mapę, i zapisuje ją do char **map, sprawdza też czy ma odpowiednie znaki ale to można przenieść
char **read_map(char *file_path)
{
    int     fd;
    int     added_row;
    char    **map;
    char    *line;

    added_row = 0;
    map = NULL;
    if (count_rows(file_path) < 0)
        return (NULL);
    line = NULL;

    map = malloc(sizeof(char *) * (count_rows(file_path) + 1));
	fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (NULL);
    }
    while ((line = get_next_line(fd)))
    {
        map[added_row++] = ft_strdup(line);
        free(line);
    }

    close(fd);
    map[added_row] = NULL;

    if (!is_01SENW(map))
    {
        // trzeba wyczyścić mapę
        printf("Error\n");
        print_map(map);
        return (NULL);
    }

    return (map);
}
// Funkcja do validacji, daje spacje żeby wyrównać długości rzędów do najdłuższego
char *fill_spaces(char *line, int max_row_len)
{
    char *new_line;
    int i;

    i = 0;
    new_line = malloc(sizeof(char) * (max_row_len + 1));
    while (line[i] && line[i] != 10 && line[i] != 13)
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