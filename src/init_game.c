#include "game.h"
#include <stdlib.h>
#include <string.h>


int find_widest_line(char **map)
{
    int max_width = 0;
    int current_width;
    int i = 0;

    if (!map)
        return 0;

    while (map[i])
    {
        current_width = strlen(map[i]); // Długość aktualnej linii
        if (current_width > max_width)
            max_width = current_width;
        i++;
    }
    return max_width;
}


// Funkcja alokująca mapę
int init_map(t_map *map)
{
    map->board = read_map(map->file_path);
    print_map(map->board);
    map->height = count_rows(map->file_path);
    
    printf("\n\n%i\n\n", find_widest_line(map->board));
    //z szerokością to nie wiem jak podejść póki co bo mapa nie musi być kwadratem chyba
    
    map->width = strlen(map->board[0]);
    return (1);
}

int init_game(t_game *game)
{
    if (!init_map(&game->map))
        return 0;

    // Inicjalizuj inne elementy gry tutaj
	// Inicjalizacja gracza
    game->player.x = 100; // Pozycja X gracza w pikselach
    game->player.y = 100; // Pozycja Y gracza w pikselach
	
    return 1;
}
