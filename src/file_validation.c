/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 13:35:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


// potrzeba sprawdzać czy przy floor i celling nie ma jakichś inncyh znaków poza whitespace liczbami i przecinkami

int invalid_char(char *line, int j)
{
    while (line[j] != '\0' && line[j] != '\n')
    {
        if (!ft_isdigit(line[j]) && line[j] != ',' && !ft_isspace(line[j]))
        {
            printf("Error: Invalid character in floor definition: '%c'\n", line[j]);
            return (1);
        }
        j++;
    }
    return (0);
}

int parse_color(char *line, int *color)
{
    int j;
    int k;

    j = 0;
    k = 0;
    while (line[j] == ' ') // Pomiń spacje na początku linii
        j++;
    if (invalid_char(line, j))
        return (0);
    k = 0; // Indeks w tablicy floor_color
    while (k < 3) // Dopóki nie odczytano wszystkich kolorów
    {
        color[k] = ft_atoi(&line[j]); // Odczytaj wartość liczby
        while (line[j] != ',' && line[j] != '\0') // Przejdź do przecinka lub końca linii
            j++;
        if (line[j] == ',') // Jeśli natrafiono na przecinek
        {
            j++;
            while (line[j] == ' ') // Pomiń spacje po przecinku
                j++;
        }
        k++; // Przejdź do kolejnego koloru
    }
    return (1);
}


int parse_texture(char *line, int j, char **texture)
{
    int len;

    j += 2; // Przesuń wskaźnik po prefiksie (np. "NO")
    while (line[j] == ' ')
        j++; // Pomiń spacje
    *texture = ft_strdup(&line[j]);
    // Usuń znak nowej linii na końcu tekstury, jeśli istnieje
    len = ft_strlen(*texture);
    if (len > 0 && (*texture)[len - 1] == '\n')
        (*texture)[len - 1] = '\0';
    if (*texture == NULL)
    {
        printf("Error: Memory allocation failed for texture\n");
        return (0);
    }
    return (1);
}



int look_for_textures(t_game *game)
{
    int i;
    int j;
    char **file;

    file = game->map.file;
    i = 0;
    while (file[i])
    {
        j = 0;
        while (file[i][j] == ' ')
            j++; // Pomiń początkowe spacje
        
        // Pomiń puste linie
        if (file[i][j] == '\0' || file[i][j] == '\n')
        {
            i++;
            continue;
        }

        // Sprawdzenie i parsowanie tekstur
        if (file[i][j] == 'N' && file[i][j + 1] == 'O' && file[i][j + 2] == ' ' && game->textures.north_texture == NULL)
        {
            if (!parse_texture(file[i], j, &game->textures.north_texture))
                return (-1);
        }
        else if (file[i][j] == 'S' && file[i][j + 1] == 'O' && file[i][j + 2] == ' ' && game->textures.south_texture == NULL)
        {
            if (!parse_texture(file[i], j, &game->textures.south_texture))
                return (-1);
        }
        else if (file[i][j] == 'W' && file[i][j + 1] == 'E' && file[i][j + 2] == ' ' && game->textures.west_texture == NULL)
        {
            if (!parse_texture(file[i], j, &game->textures.west_texture))
                return (-1);
        }
        else if (file[i][j] == 'E' && file[i][j + 1] == 'A' && file[i][j + 2] == ' ' && game->textures.east_texture == NULL)
        {
            if (!parse_texture(file[i], j, &game->textures.east_texture))
                return (-1);
        }
        else if (file[i][j] == 'F' && file[i][j + 1] == ' ' && game->textures.floor_color[0] == -1)
        {
            j++;
            if (!parse_color(&file[i][j], game->textures.floor_color))
                return (-1);
        }
        else if (file[i][j] == 'C' && file[i][j + 1] == ' ' && game->textures.ceiling_color[0] == -1)
        {
            j++;
            if (!parse_color(&file[i][j], game->textures.ceiling_color))
                return (-1);
        }
        else
        {
            if (game->textures.north_texture != NULL && game->textures.south_texture != NULL && game->textures.west_texture != NULL && game->textures.east_texture != NULL && game->textures.floor_color[0] != -1 && game->textures.ceiling_color[0] != -1)
                return (i); // Zwróć liczbę odczytanych linii gdy wszystkie dane zostały odczytane i znaleziono inne znaki
            printf("Error: Invalid line in textures: %s or those are not textures\n ", file[i]);
            return (-1);
        }
        i++;
    }
    return (i); // Zwróć liczbę odczytanych linii gdy nie znaleziono błędów
}


void load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->window.mlx_ptr, path, &texture->width, &texture->height);
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

void load_textures(t_game *game)
{
    load_texture(game, &game->textures.north, game->textures.north_texture);
    load_texture(game, &game->textures.south, game->textures.south_texture);
    load_texture(game, &game->textures.west, game->textures.west_texture);
    load_texture(game, &game->textures.east, game->textures.east_texture);
}

// Funkcja główna do odczytu danych gry i zwrócenia liczby odczytanych linii
int read_textures(t_game *game)
{
    int line_count;

    line_count = look_for_textures(game);
    if (line_count == -1)
    {
        return (0);
    }
    //printf("%i\n", line_count);
    game->textures.height_util = line_count;
    return (1);
}
