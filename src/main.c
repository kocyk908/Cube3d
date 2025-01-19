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
    if (ft_strcmp(&game.map.file_path[ft_strlen(game.map.file_path) - 4], ".cub") != 0)
    {
        printf("Error: Invalid file extension\n");
        return (1);
    }
    game.map.file = read_file(game.map.file_path);
    if (game.map.file == NULL)
    {
        printf("Error: Failed to read file\n");
        return (1);
    }

    if (!read_textures(&game))
    {
        printf("read_textures issue");
        return (0);
    }
    game.map.board = read_map(&game);

    game.map.board_with_spaces = map_with_spaces(game);
    game.map.width = find_longest_row_length(game.map.board);
    game.map.height = game.textures.height_util;

    //      validacja mapy
    
    if (!is_map_valid(game))
    {
        printf("is_map_valid error\n");
        return 0;
    }

    player_pos(&game);


    //      Inicjalizacja okna
    if (!init_window(&game))
    {
        printf("Error: Failed to initialize window\n");
        return (1);
    }

    load_textures(&game); // ustawianie textur do t_texture north itd

          //  return 0;

    game.player.dir_x = 1;
    game.player.dir_y = 0;
    game.player.fov = PI/3;

    // Ustawienie obsługi zdarzeń
    //place_images_in_game(&game);
    
    mlx_hook(game.window.win_ptr, 2, 1L<<0, key_pressed, &game); 
    mlx_hook(game.window.win_ptr, 3, 1L<<1, key_release, &game);
    mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);

     //mlx_key_hook(game.window.win_ptr, controls_working, &game);
    mlx_loop_hook(game.window.mlx_ptr, draw_loop, &game);
    mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);
    mlx_loop(game.window.mlx_ptr); //open window

    return (0);
}

void move_player(t_game *game)
{
    double speed;
    double angle_speed;
    double cos_angle;
    double sin_angle;
    double new_x;
    double new_y;

    cos_angle = cos(game->player.angle);
    sin_angle = sin(game->player.angle);
    angle_speed = 0.01;
    speed = SPEED;

    // Obrót gracza
    if (game->player.left_rotate)
        game->player.angle -= angle_speed;
    if (game->player.right_rotate)
        game->player.angle += angle_speed;
    if (game->player.angle > 2 * PI)
        game->player.angle = 0;
    if (game->player.angle < 0)
        game->player.angle = 2 * PI;

    // Ruch do przodu
    if (game->player.key_up)
    {
        new_x = game->player.x + cos_angle * speed;
        new_y = game->player.y + sin_angle * speed;
        if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    // Ruch do tyłu
    if (game->player.key_down)
    {
        new_x = game->player.x - cos_angle * speed;
        new_y = game->player.y - sin_angle * speed;
        if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    // Ruch w lewo
    if (game->player.key_left)
    {
        new_x = game->player.x + sin_angle * speed;
        new_y = game->player.y - cos_angle * speed;
        if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    // Ruch w prawo
    if (game->player.key_right)
    {
        new_x = game->player.x - sin_angle * speed;
        new_y = game->player.y + cos_angle * speed;
        if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
}

bool touch(double px, double py, t_game *game)
{
    if (px < 0 || px >= game->map.width * BLOCK || py < 0 || py >= game->map.height * BLOCK)
        return (true);
    int x = (int)(py / BLOCK);
    int y = (int)(px / BLOCK);
    if(game->map.board_with_spaces[x][y] == '1')
    {
        return (true);
    }
    return (false);
}

double distance(double x, double y)
{
    return sqrt(x * x + y * y);
}

double fixed_dist(double x1, double y1, double x2, double y2, t_game *game)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    double angle = atan2(delta_y, delta_x) - game->player.angle;
    double fixed_dist = distance(delta_x, delta_y) * cos(angle);

    return fixed_dist;
}

void draw_textured_wall(t_game *game, t_texture *texture, int column, int start, int end, double wall_x, double wall_height)
{
    double step = (double)texture->height / wall_height; // Skok w teksturze na piksel
    double tex_pos = (start - HEIGHT / 2 + wall_height / 2) * step; // Pozycja początkowa w teksturze

    for (int y = start; y < end; y++)
    {
        int tex_y = (int)tex_pos & (texture->height - 1); // Współrzędna Y na teksturze
        tex_pos += step; // Przesunięcie pozycji na teksturze

        int tex_x = (int)(wall_x * texture->width) & (texture->width - 1); // Współrzędna X na teksturze

        // Pobranie koloru piksela z tekstury
        int color = *(int *)(texture->data + (tex_y * texture->size_line + tex_x * (texture->bpp / 8)));

        // Rysowanie piksela
        put_pixel(column, y, color, game);
    }
}

void draw_line(t_player *player, t_game *game, double ray_angle, int column)
{
    double ray_x = player->x;
    double ray_y = player->y;
    double cos_angle = cos(ray_angle);
    double sin_angle = sin(ray_angle);

    // Znajdź punkt trafienia promienia
    while (!touch(ray_x * BLOCK, ray_y * BLOCK, game))
    {
        ray_x += cos_angle * 0.01;
        ray_y += sin_angle * 0.01;
    }

    // Oblicz dystans i wysokość ściany
    double dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
    double wall_height = (BLOCK / dist) * (WIDTH / 2);
    int start = (HEIGHT - wall_height) / 2;
    int end = start + wall_height;

    // Ustal kierunek ściany (north, south, west, east)
    int wall_direction;
    if (fabs(cos_angle) > fabs(sin_angle))
        wall_direction = (cos_angle > 0) ? 3 : 2; // East or West
    else
        wall_direction = (sin_angle > 0) ? 1 : 0; // South or North

    // Wybierz teksturę
    t_texture *texture;
    if (wall_direction == 0)
        texture = &game->textures.north;
    else if (wall_direction == 1)
        texture = &game->textures.south;
    else if (wall_direction == 2)
        texture = &game->textures.west;
    else
        texture = &game->textures.east;

    // Oblicz pozycję na teksturze
    double wall_x;
    if (wall_direction == 2 || wall_direction == 3) // West or East
        wall_x = ray_y - floor(ray_y);
    else // North or South
        wall_x = ray_x - floor(ray_x);

    // Renderuj ścianę z teksturą
    draw_textured_wall(game, texture, column, start, end, wall_x, wall_height);
}

int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    move_player(game); // Obsługa ruchu gracza
    clear_image(game); // Czyszczenie bufora obrazu

    double ray_angle = player->angle - (player->fov / 2);
    double angle_step = player->fov / WIDTH;

    for (int column = 0; column < WIDTH; column++)
    {
        draw_line(player, game, ray_angle, column); // Rysuj ścianę dla każdej kolumny
        ray_angle += angle_step;
    }

    mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, game->window.img, 0, 0);
    return (0);
}


void set_angle(t_game *game)
{
    if (game->player.NSWE == 'N')
        game->player.angle = 3 * PI / 2;
    if (game->player.NSWE == 'S')
        game->player.angle = PI / 2;
    if (game->player.NSWE == 'E')
        game->player.angle = 0;
    if (game->player.NSWE == 'W')
        game->player.angle = PI;
}

void player_pos(t_game *game)
{
    char    **mapa;
    int i;
    int j;

    i = 0;
    j = 0;
    mapa = game->map.board;
    while (mapa[i])
    {
        j = 0;
        while (mapa[i][j])
        {
            if (mapa[i][j] == 'N' || mapa[i][j] == 'S' || mapa[i][j] == 'E' || mapa[i][j] == 'W')
            {
                game->player.NSWE = mapa[i][j];
                game->player.x = j;
                game->player.y = i;
            }
            j++;
        }
        i++;
    }
    set_angle(game);
    return ;
}