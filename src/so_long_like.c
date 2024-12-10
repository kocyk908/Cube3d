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

static void	draw_element(t_game *game, int height, int width)
{
	char	elem;
	int		x;
	int		y;

	elem = game->map.board_with_spaces[height][width];
	set_variables(&x, &y, height, width);
	if (elem == '1')
		mlx_put_image_to_window(game->window.mlx_ptr,
			game->window.win_ptr, game->textures.north_texture, x, y);
}

void	adding_in_graphics(t_game *game)
{
	int	x;
	int	y;

    place_images_in_game(game);

    printf("hello");
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

int	controls_working(t_game *game)
{
	adding_in_graphics(game);
	return (1);
}
