#ifndef GAME_H
#define GAME_H

#include "cube3d.h"

typedef struct s_player {
    double x;    // Pozycja X gracza
    double y;    // Pozycja Y gracza
    double dir_x; // Kierunek X
    double dir_y; // Kierunek Y
    double fov;   // Pole widzenia
} t_player;

typedef struct s_map {
    char *file_path; // Ścieżka do pliku z mapą
    int width;
    int height;
    char **board; // Reprezentacja mapy (np. tablica znaków '1', '0')
} t_map;

typedef struct s_game {
    t_window window;  // Dane okna MLX
    t_player player;  // Dane gracza
    t_map map;        // Dane mapy
} t_game;

// Prototypy funkcji
int init_game(t_game *game);
int render_frame(void *param);
int main_loop(t_game *game);
int init_map(t_map *map);
int close_window(t_game *game);
char **map_with_spaces(t_game game);

#endif
