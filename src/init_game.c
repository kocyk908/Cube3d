#include "game.h"
#include <stdlib.h>
#include <string.h>


int find_widest_line(char **map)
{
    int max_width = 0;
    int current_width;
    int i = 0;

    if (!map)
        return 0;

    while (map[i])
    {
        current_width = strlen(map[i]); // Długość aktualnej linii
        if (current_width > max_width)
            max_width = current_width;
        i++;
    }
    return max_width;
}


void init_map(t_map *map)
{
    map->file_path = NULL;
    map->width = 0;
    map->height = 0;
    map->file = NULL;
    map->board = NULL;
    map->board_with_spaces = NULL;
}

void init_player(t_player *player)
{
    player->x = 0;
    player->y = 0;
    player->dir_x = 0;
    player->dir_y = 0;
    player->fov = 0;
}

void init_textures(t_textures *textures)
{
    textures->north_texture = NULL;
    textures->south_texture = NULL;
    textures->west_texture = NULL;
    textures->east_texture = NULL;
    textures->floor_color[0] = -1;
    textures->ceiling_color[0] = -1;
    textures->lines_gnl = 0;
}

int init_window(t_game *game)
{
    game->window.mlx_ptr = mlx_init();
    if (game->window.mlx_ptr == NULL)
        return (0);
    game->window.win_ptr = mlx_new_window(game->window.mlx_ptr, game->map.width * 40, game->map.height * 40, "Giereczka");
    if (game->window.win_ptr == NULL)
    {
        free(game->window.mlx_ptr);
        return (0);
    }
    return (1);
}
// Funkcja alokująca map

int init_game(t_game *game)
{
    init_map(&game->map);
    init_player(&game->player);
    init_textures(&game->textures);
    return (1);
}
