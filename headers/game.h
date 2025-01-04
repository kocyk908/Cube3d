#ifndef GAME_H
#define GAME_H

# define WIDTH 1280
# define HEIGHT 720

# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# define SPEED 0.02

#include "cube3d.h"

typedef struct s_player {
    double x;    // Pozycja X gracza
    double y;    // Pozycja Y gracza
    double angle; // Kąt patrzenia gracza

    bool    key_up;
    bool    key_down;
    bool    key_left;
    bool    key_right;

    bool    left_rotate;
    bool    right_rotate;

    double dir_x; // Kierunek X
    double dir_y; // Kierunek Y
    double fov;   // Pole widzenia
    char    NSWE;
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
    int height_util; // Liczba linii wczytanych przez GNL dla tekstur i kolorów (pozostale powinny być dla mapy)
} t_textures;

typedef struct s_window
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img;

    char    *data;
    int     bpp;
    int     size_l;
    int     endian;
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

int read_textures(t_game *game);
int ft_isspace(char c);

char **read_map(t_game *game);
char **read_file(char *file_path);


void player_pos(t_game *game);





// FUNKCJE Z FILMU
void    draw_square(int x, int y, int size, int color, t_game *game);
int key_pressed(int command, t_game *game);
int key_release(int command, t_game *game);
int draw_loop(t_game *game);
void    clear_image(t_game *game);
void    draw_map(t_game *game);
void    put_pixel(int x, int y, int color, t_game *game);


#endif
