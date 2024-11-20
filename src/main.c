#include "cube3d.h"
#include "game.h" // Dodajemy plik nagłówkowy, gdzie zdefiniujemy strukturę gry i podstawowe funkcje.


int main(int argc, char **argv)
{
    t_game game;

    //mapa////////////////////////
    char **map;

    map = NULL;
    if (argc != 2)
    {
        printf("Usage: %s <map_file.cub>\n", argv[0]);
        return 1;
    }
    map = read_map(argv[1]);
    if (!map)
    {
        printf("Failed to read map.\n");
        return (1);
    }
    free_map(map); //na później
    //mapa////////////////////////


    // Inicjalizacja okna
    game.window.mlx_ptr = mlx_init();
    if (game.window.mlx_ptr == NULL)
        return (1);
    game.window.win_ptr = mlx_new_window(game.window.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Giereczka");
    if (game.window.win_ptr == NULL)
    {
        free(game.window.mlx_ptr);
        return (1);
    }

    // Inicjalizacja danych gry
    if (!init_game(&game)) // Funkcja do inicjalizacji gracza, mapy itp.
    {
        close_window(&game);
        return (1);
    }

    // Ustawienie obsługi zdarzeń
    mlx_loop_hook(game.window.mlx_ptr, render_frame, &game);
    mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);
    mlx_loop(game.window.mlx_ptr);

    return (0);
}
