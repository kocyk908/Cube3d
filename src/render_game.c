#include "game.h"

void render_player(t_game *game) {
    int x = (int)game->player.x;
    int y = (int)game->player.y;

    // Rysowanie gracza jako małego kwadratu
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            int draw_x = x + i;
            int draw_y = y + j;

            if (draw_x >= 0 && draw_x < WIN_WIDTH && draw_y >= 0 && draw_y < WIN_HEIGHT)
                mlx_pixel_put(game->window.mlx_ptr, game->window.win_ptr, draw_x, draw_y, 0xFFFFFF); // Kolor biały
        }
    }
}

int render_frame(void *param) {
    t_game *game = (t_game *)param;

    mlx_clear_window(game->window.mlx_ptr, game->window.win_ptr);

    // Rysowanie gracza
    render_player(game);

    return (0);
}

