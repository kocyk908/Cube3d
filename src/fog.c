#include "game.h"

int apply_fog(int color, double distance)
{
    double fog_factor = exp(-distance * 0.05); // Im dalej, tym ciemniej
    if (fog_factor > 1.0) fog_factor = 1.0;
    if (fog_factor < 0.1) fog_factor = 0.1; // Minimalna widoczność

    int r = ((color >> 16) & 0xFF) * fog_factor;
    int g = ((color >> 8) & 0xFF) * fog_factor;
    int b = (color & 0xFF) * fog_factor;

    return (r << 16) | (g << 8) | b;
}

//int rgb_to_int(int r, int g, int b)
//{
//    return (r << 16) | (g << 8) | b;
//}

void draw_floor_and_ceiling(t_game *game)
{
    int x, y;
    int floor_base = 0x555555;
    int ceiling_base = 0x333333;

    for (y = 0; y < HEIGHT; y++)
    {
        double distance = HEIGHT / (2.0*y - HEIGHT); // Przybliżona odległość

        int color = (y < HEIGHT / 2) ? ceiling_base : floor_base;
        color = apply_fog(color, distance);

        for (x = 0; x < WIDTH; x++)
            put_pixel(x, y, color, game);
    }
}
