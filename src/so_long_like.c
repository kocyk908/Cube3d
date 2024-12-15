#include "game.h"

void	place_images_in_game(t_game *game)
{
	int	i;
	int	j;

	game->textures.east_texture = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"dirt.xpm", &i, &j);
	game->textures.north_texture = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"dirt.xpm", &i, &j);
	game->textures.south_texture = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"dirt.xpm", &i, &j);
	game->textures.west_texture = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"dirt.xpm", &i, &j);
}


void	set_variables(int *x, int *y, int height, int width)
{
	*x = width * 40;
	*y = height * 40;
}

static void draw_element(t_game *game, int height, int width)
{
    char elem = game->map.board_with_spaces[height][width];
    int x, y;
    set_variables(&x, &y, height, width);

    if (elem == '1') // Ściana
        mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, game->textures.north_texture, x, y);
}

void	adding_in_graphics(t_game *game)
{
	int	x;
	int	y;

    //printf("hello");
	x = 0;
	while (x < game->map.height)
	{
		y = 0;
		while (game->map.board_with_spaces[x][y])
		{
			draw_element(game, x, y);
			y++;
		}
		x++;
	}
}

void keyboard_w(t_game *game, double speed)
{
    int i;
    int j;
    int steps;

    i = (int)game->player.x;
    j = (int)game->player.y;
    steps = speed;

    while (steps > 0)
    {
        j--;
        if (game->map.board_with_spaces[j][i] == '1')
        {
            j++; // Step back to the last valid position
            break;
        }
        steps--;
    }

    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = '0';
    game->player.y = j;
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = game->player.NSWE;
    return;
}

void keyboard_s(t_game *game, double speed)
{
    int i;
    int j;
    int steps;

    i = (int)game->player.x;
    j = (int)game->player.y;
    steps = speed;

    while (steps > 0)
    {
        j++;
        if (game->map.board_with_spaces[j][i] == '1')
        {
            j--; // Step back to the last valid position
            break;
        }
        steps--;
    }

    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = '0';
    game->player.y = j;
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = game->player.NSWE;
    return;
}

void keyboard_a(t_game *game, double speed)
{
    int i;
    int j;
    int steps;

    i = (int)game->player.x;
    j = (int)game->player.y;
    steps = speed;

    while (steps > 0)
    {
        i--;
        if (game->map.board_with_spaces[j][i] == '1')
        {
            i++; // Step back to the last valid position
            break;
        }
        steps--;
    }

    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = '0';
    game->player.x = i;
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = game->player.NSWE;
    return;
}

void keyboard_d(t_game *game, double speed)
{
    int i;
    int j;
    int steps;

    i = (int)game->player.x;
    j = (int)game->player.y;
    steps = speed;

    while (steps > 0)
    {
        i++;
        if (game->map.board_with_spaces[j][i] == '1')
        {
            i--; // Step back to the last valid position
            break;
        }
        steps--;
    }
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = '0';
    game->player.x = i;
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = game->player.NSWE;
    return;
}

int key_pressed(int command, t_game *game)
{
	printf("controls working command -> %i\n", command);
    if (command == W) // Strzałka w górę
        game->player.key_up = true;
	else if (command == S)
		game->player.key_down = true;
	else if (command == A)
		game->player.key_left = true;
	else if (command == D)
		game->player.key_right = true;
    if (command == LEFT)
        game->player.left_rotate = true;
    else if (command == RIGHT)
        game->player.right_rotate = true;
    return (0);

}

int key_release(int command, t_game *game)
{
    if (command == W)
        game->player.key_up = false;
	else if (command == S)
		game->player.key_down = false;
	else if (command == A)
		game->player.key_left = false;
	else if (command == D)
		game->player.key_right = false;
    if (command == LEFT)
        game->player.left_rotate = false;
    else if (command == RIGHT)
        game->player.right_rotate = false;
    return (0);
}