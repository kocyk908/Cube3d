#include "game.h"

void perform_dda(t_game *game)
{
    t_ray *ray = &game->ray;

    while (!ray->hit)  // Dopóki nie trafi w ścianę
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // Pionowa ściana
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // Pozioma ściana
        }

        // Sprawdzenie, czy promień trafił w ścianę
        if (game->map.board[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void calculate_texture(t_game *game)
{
    t_ray *ray = &game->ray;

    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->dir_y;

    // Obliczenie pozycji trafienia w ścianę
    if (ray->side == 0)
        ray->wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
    else
        ray->wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);

    // Pobranie X tekstury
    ray->tex_x = (int)(ray->wall_x * (double)game->textures.north.width);
    if (ray->side == 0 && ray->dir_x > 0)
        ray->tex_x = game->textures.north.width - ray->tex_x - 1;
    if (ray->side == 1 && ray->dir_y < 0)
        ray->tex_x = game->textures.north.width - ray->tex_x - 1;
}

