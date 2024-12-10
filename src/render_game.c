#include "game.h"

void render_player(t_game *game)
{
    int x = game->player.x;
    int y = game->player.y;

    for (int i = -4; i <= 4; i++)
    {
        for (int j = -4; j <= 4; j++)
        {
            int draw_x = x + i;
            int draw_y = y + j;

            if (draw_x >= 0 && draw_x < WIN_WIDTH && draw_y >= 0 && draw_y < WIN_HEIGHT)
                mlx_pixel_put(game->window.mlx_ptr, game->window.win_ptr, draw_x, draw_y, 0xFFFFFF); // Kolor biały
        }
    }
}

int handle_key_press(int keycode, t_game *game)
{
    if (keycode == 65362)
        game->player.y -= 1;
    else if (keycode == 65364)
        game->player.y += 1;
    else if (keycode == 65361)
        game->player.x -= 1;
    else if (keycode == 65363)
        game->player.x += 1;

    return (0);
}

int render_frame(void *param) {
    t_game *game = (t_game *)param;

    mlx_clear_window(game->window.mlx_ptr, game->window.win_ptr);

    // Rysowanie gracza
    //render_wall(game);
    render_player(game);

    return (0);
}
