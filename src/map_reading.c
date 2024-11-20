#include "cube3d.h"

// sprawdzanie czy linia mapy jest okej
// narazie raczej kwadratowa mapa do poprawy
int is_valid_line(char *line)
{
    size_t i;
	i = 0;

    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' &&
            line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
        {
			if (ft_strlen(line) < 5)
			{
				return (0);
			}
			if (i == ft_strlen(line) - 2 && line[i] == 13 && line[i + 1] == 10)
				return (1);
			return (0);
        }
        i++;
    }
    return (1);
}

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
        if (!is_valid_line(line))
        {
            // trzeba wyczyścić mapę
            printf("Invalid map line: %s\n", line);
            return (NULL);
        }
        map[added_row++] = ft_strdup(line);
        free(line);
    }
    close(fd);
    map[added_row] = NULL;
    return (map);
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