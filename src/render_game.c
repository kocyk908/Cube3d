#include "game.h"

void    put_pixel(int x, int y, int color, t_game *game)
{
    int index;

    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;
    index = y * game->window.size_l + x * (game->window.bpp / 8);    
    game->window.data[index] = color & 0xFF;
    game->window.data[index + 1] = (color >> 8) & 0xFF;
    game->window.data[index + 2] = (color >> 16) & 0xFF;
}

void    draw_square(int x, int y, int size, int color, t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            put_pixel(x + i, y + j, color, game);
            j++;
        }
        i++;
    }
}

void    clear_image(t_game *game)
{
        int i;
        int j;

        i = 0;
        while (i < WIDTH)
        {
            j = 0;
            while (j < HEIGHT)
            {
                put_pixel(i, j, 0, game);
                j++;
            }
            i++;
        }
}

void    draw_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (game->map.board_with_spaces[i][j])
        {
            if (game->map.board_with_spaces[i][j] == '1')
                draw_square(j * 64, i * 64, 64, 0xFFFFFF, game);
            j++;
        }
        i++;
    }
}