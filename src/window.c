#include "game.h"
#include "window.h"

int close_window(t_game *game)
{
    if (game->window.win_ptr)
        mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
    if (game->window.mlx_ptr)
        free(game->window.mlx_ptr);
    exit(0);
    return (0);
}

int main_loop(t_game *game)
{
    // Tutaj będą wywoływane funkcje odpowiadające za rysowanie sceny, obsługę gracza itp.
    render_frame(game);  // Funkcja odpowiedzialna za raycasting i rysowanie.
    return (0);
}
