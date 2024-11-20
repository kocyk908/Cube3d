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

char **read_map(char *file_path)
{
    int     fd;
    int     map_size;
    char    **map;
    char    *line;

    map = NULL;
    map_size = 0;
    line = NULL;
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
            printf("Invalid map line: %s\n", line);
            free(line);

            int i;
			i = 0;
            while (i < map_size)
            {
                free(map[i]);
                i++;
            }
            free(map);
            close(fd);
            return (NULL);
        }

        // Tworzenie nowej tablicy za pomocą malloc
        char **new_map;
		new_map = malloc(sizeof(char *) * (map_size + 1));
        if (!new_map)
        {
            perror("Error allocating memory");
            free(line);

            int i;
			i = 0;
            while (i < map_size)
            {
                free(map[i]);
                i++;
            }
            free(map);
            close(fd);
            return (NULL);
        }

        // Kopiowanie danych ze starej tablicy do nowej
        int i;
		i = 0;
        while (i < map_size)
        {
            new_map[i] = map[i];
            i++;
        }

        // Zwolnienie starej tablicy
        free(map);

        // Dodanie nowego wiersza
        new_map[map_size] = line;
        map = new_map;
        map_size++;
    }
    close(fd);

    char **final_map = malloc(sizeof(char *) * (map_size + 1));
    if (!final_map)
    {
        perror("Error allocating memory");

        int i;
		i = 0;
        while (i < map_size)
        {
            free(map[i]);
            i++;
        }
        free(map);
        return (NULL);
    }

    int	i;
	i = 0;
    while (i < map_size)
    {
        final_map[i] = map[i];
        i++;
    }
    final_map[map_size] = NULL;

    free(map);
    return final_map;
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