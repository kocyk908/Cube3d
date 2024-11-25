#include "cube3d.h"
#include "game.h" // Dodajemy plik nagłówkowy, gdzie zdefiniujemy strukturę gry i podstawowe funkcje.


int main(int argc, char **argv)
{
    t_game game;

    //mapa////////////////////////
    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return (1);
    }
    game.map.file_path = argv[1];
    game.map.board = read_map(game.map.file_path);
    game.map.board_with_spaces = map_with_spaces(game);

    game.map.height = count_rows(game.map.file_path);
    game.map.width = find_longest_row_length(game.map.board);
    print_map(game.map.board);
    printf("\n\n");

    // validacja mapy
    
    if (!is_map_valid(game))
    {
        printf("is_map_valid error\n");
        return 0;
    }

    char **map = map_with_spaces(game);
    if (!map)
    {
        printf("Invalid map.\n");
        return (1);
    }


    //print_map(map);
    return (0);
    //free_map(map); //na później
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
