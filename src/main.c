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
void draw_line(t_player *player, t_game *game, double start_x, int i)
{
    t_ray *ray = &game->ray;

    // Inicjalizacja promienia
    ray->dir_x = cos(start_x);
    ray->dir_y = sin(start_x);
    ray->map_x = (int)player->x;
    ray->map_y = (int)player->y;

    // Obliczenie wartości dla DDA
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);

    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
    }
    
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
    }

    // Wykonanie DDA do znalezienia ściany
    ray->hit = 0;
    perform_dda(game);

    // Obliczenie dystansu do ściany
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;

    // Korekcja efektu rybiego oka
    ray->perp_wall_dist *= cos(player->angle - atan2(ray->dir_y, ray->dir_x));

    // Obliczenie wysokości ściany
    int lineHeight = (int)(HEIGHT / ray->perp_wall_dist);

    // Określenie górnej i dolnej krawędzi ściany
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

    // Wybór tekstury na podstawie kierunku uderzenia
    t_texture *tex;
    if (ray->side == 0)
    {
        if (ray->step_x > 0)
            tex = &game->textures.east;
        else
            tex = &game->textures.west;
    }
    else
    {
        if (ray->step_y > 0)
            tex = &game->textures.south;
        else
            tex = &game->textures.north;
    }

    // Obliczenie X-owej współrzędnej tekstury
    if (ray->side == 0)
        ray->wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
    else
        ray->wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
    
    ray->wall_x -= floor(ray->wall_x);
    ray->tex_x = (int)(ray->wall_x * (double)tex->width);

    if (ray->side == 0 && ray->dir_x > 0)
        ray->tex_x = tex->width - ray->tex_x - 1;
    if (ray->side == 1 && ray->dir_y < 0)
        ray->tex_x = tex->width - ray->tex_x - 1;

    // Rysowanie ściany
    int y = drawStart;
    while (y < drawEnd)
    {
        int tex_y = (int)(((y - drawStart) * tex->height) / (double)lineHeight);
        if (tex_y < 0) tex_y = 0;  // Zabezpieczenie przed przekroczeniem zakresu

        int tex_offset = (tex_y * tex->size_line) + (ray->tex_x * (tex->bpp / 8));
        int color = *(int *)(tex->data + tex_offset);

        put_pixel(i, y, color, game);
        y++;
    }
}



// void draw_line(t_player *player, t_game *game, double start_x, int i)
// {
//     double cos_angle = cos(start_x);
//     double sin_angle = sin(start_x);
//     double ray_x = player->x * BLOCK;
//     double ray_y = player->y * BLOCK;

//     while(!touch(ray_x, ray_y, game))
//     {
//         //put_pixel(ray_x, ray_y, 0xFF0000, game);
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//     }

//     double dist = fixed_dist(player->x * BLOCK, player->y * BLOCK, ray_x, ray_y, game);
//     double height = (BLOCK / dist) * (WIDTH / 2);
//     int start = (HEIGHT - height) / 2;
//     int end = start + height;

//     while(start < end)
//     {

//         put_pixel(i, start, 0xFF0000, game);
//         start++;
//     }
// }

int draw_loop(t_game *game)
{
    t_player *player;
    
    player = &game->player;
    move_player(game);
    clear_image(game);
    //draw_square(player->x * BLOCK, player->y * BLOCK, 10, 0x0000FF, game);
    //draw_map(game);
    
    double fraction = game->player.fov / WIDTH;
    double start_x = player->angle - (game->player.fov / 2);
    int i = 0;
    while(i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
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