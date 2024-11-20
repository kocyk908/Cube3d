#include "game.h"
#include <stdlib.h>
#include <string.h>

// Funkcja alokująca mapę
int init_map(t_map *map)
{
    char **board;
    //int height;

    board = read_map(map->file_path);

    print_map(board);
    return 1;
    //height = sizeof(rows) / sizeof(rows[0]) - 1; // Odejmujemy 1 dla NULL
    //map->data = malloc(sizeof(char *) * height);
    //if (!map->data)
    //    return 0;

    //for (int i = 0; i < height; i++) {
    //    map->data[i] = strdup(rows[i]);
    //    if (!map->data[i]) {
    //        // W razie błędu zwalniamy wcześniej zaalokowaną pamięć
    //        while (--i >= 0)
    //            free(map->data[i]);
    //        free(map->data);
    //        return 0;
    //    }
    //}
    //map->width = strlen(rows[0]);
    //map->height = height;
    //return 1;
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
