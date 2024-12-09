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

    place_images_in_game(game);

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






static int keyboard_w(t_game *game)
{
    int i = game->player.x;
    int j = game->player.y;

    j--;
    if (game->map.board_with_spaces[j][i] == '1')
        return (0);
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = '0';
    game->player.y = j;
    game->map.board_with_spaces[(int)game->player.y][(int)game->player.x] = 'P'; // Assuming 'P' represents the player
    return (1);
}

int controls_working(int command, t_game *game)
{
    int works = 0;

    if (command == 65362) // Strzałka w górę
        works = keyboard_w(game);

    if (works)
    {
        mlx_clear_window(game->window.mlx_ptr, game->window.win_ptr);
        adding_in_graphics(game);
    }
    return (1);
}