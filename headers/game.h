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
    char **file;
    char **board; // Reprezentacja mapy (np. tablica znaków '1', '0')
    char **board_with_spaces;
} t_map;

typedef struct s_textures {
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color[3];  // RGB dla F
    int ceiling_color[3]; // RGB dla C
    int lines_gnl; // Liczba linii wczytanych przez GNL dla tekstur i kolorów (pozostale powinny być dla mapy)
} t_textures;

typedef struct s_window
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_window;


typedef struct s_game {
    t_window window;  // Dane okna MLX
    t_player player;  // Dane gracza
    t_map map;        // Dane mapy
    t_textures textures; // Dane tekstur
} t_game;


// Prototypy funkcji
int init_game(t_game *game);
int init_window(t_game *game);
int render_frame(void *param);
int main_loop(t_game *game);
void init_map(t_map *map);
int close_window(t_game *game);
char **map_with_spaces(t_game game);
int is_map_valid(t_game game);
int is_one_player(char **map);
int is_map_closed(t_game game);
int find_longest_row_length(char **map);
int is_map_closed_up(t_game game);
int is_map_closed_left(t_game game);
int is_map_closed_down(t_game game);
int is_map_closed_right(t_game game);

int are_all_ones_connected(t_game game);

void read_textures(t_game *game);
int ft_isspace(char c);

char **read_map(t_game *game);
char **read_file(char *file_path);

#endif
