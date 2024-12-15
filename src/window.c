#include "game.h"
#include "cube3d.h"

int close_window(t_game *game)
{
    if (game->window.win_ptr)
        mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
    if (game->window.mlx_ptr)
        free(game->window.mlx_ptr);
    exit(0);
    return (0);
}
