#include "cube3d.h"
#include "game.h" // Dodajemy plik nagłówkowy, gdzie zdefiniujemy strukturę gry i podstawowe funkcje.


int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return (1);
    }

    init_game(&game);

    game.map.file_path = argv[1];
    game.map.file = read_file(game.map.file_path);

    read_textures(&game);
    game.map.board = read_map(&game);

    game.map.board_with_spaces = map_with_spaces(game);
    game.map.width = find_longest_row_length(game.map.board);
    game.map.height = count_rows(game.map.file_path) - game.textures.lines_gnl;
    print_map(game.map.board);
    printf("\n\n");

    //      validacja mapy
    
    if (!is_map_valid(game))
    {
        printf("is_map_valid error\n");
        return 0;
    }

    //char **map = map_with_spaces(game);
    //if (!map)
    //{
    //    printf("Invalid map.\n");
    //    return (1);
    //}


    //print_map(map);
    //                return (0);

    // Inicjalizacja okna
    if (!init_window(&game))
    {
        printf("Error: Failed to initialize window\n");
        return (1);
    }

    //// Inicjalizacja danych gry
    //if (!init_game(&game)) // Funkcja do inicjalizacji gracza, mapy itp.
    //{
    //    close_window(&game);
    //    return (1);
    //}

    // Ustawienie obsługi zdarzeń
    mlx_loop_hook(game.window.mlx_ptr, render_frame, &game);
    mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);
    mlx_loop(game.window.mlx_ptr);

    return (0);
}
