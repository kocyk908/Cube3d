#include "cube3d.h"
#include "game.h" // Dodajemy plik nagłówkowy, gdzie zdefiniujemy strukturę gry i podstawowe funkcje.

int main(void)
{
    t_game game;

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
