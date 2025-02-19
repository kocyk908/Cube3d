/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 13:34:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "game.h"

int	main(int argc, char **argv)
{
	t_game	game;

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
	if (!is_map_valid(game))
	{
		printf("is_map_valid error\n");
		return (0);
	}
	player_pos(&game);
	if (!init_window(&game))
	{
		printf("Error: Failed to initialize window\n");
		return (1);
	}
	load_textures(&game);
	mlx_hook(game.window.win_ptr, 2, 1L<<0, key_pressed, &game); 
	mlx_hook(game.window.win_ptr, 3, 1L<<1, key_release, &game);
	mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);
	mlx_loop_hook(game.window.mlx_ptr, draw_loop, &game);
	mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);
	mlx_loop(game.window.mlx_ptr);

	mlx_clear_window(game.window.mlx_ptr, game.window.win_ptr);
	mlx_destroy_window(game.window.mlx_ptr, game.window.win_ptr);
	mlx_destroy_image(game.window.mlx_ptr, game.window.img);
	mlx_destroy_display(game.window.mlx_ptr);
	free(game.window.mlx_ptr);

	free_map(game.map.board);
	free_map(game.map.board_with_spaces);
	free(game.map.file);

	return (0);
}

void	move_player(t_game *game)
{
	double		speed;
	double		angle_speed;
	double		new_x;
	double		new_y;

	speed = SPEED;
	angle_speed = 0.05;
	new_x = 0;
	new_y = 0;
	if (game->player.right_rotate)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(angle_speed) - game->player.dir_y * sin(angle_speed);
		game->player.dir_y = oldDirX * sin(angle_speed) + game->player.dir_y * cos(angle_speed);

		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(angle_speed) - game->player.plane_y * sin(angle_speed);
		game->player.plane_y = oldPlaneX * sin(angle_speed) + game->player.plane_y * cos(angle_speed);
	}
	if (game->player.left_rotate)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-angle_speed) - game->player.dir_y * sin(-angle_speed);
		game->player.dir_y = oldDirX * sin(-angle_speed) + game->player.dir_y * cos(-angle_speed);

		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-angle_speed) - game->player.plane_y * sin(-angle_speed);
		game->player.plane_y = oldPlaneX * sin(-angle_speed) + game->player.plane_y * cos(-angle_speed);
	}
	if (game->player.key_up)
	{
		new_x = game->player.x + game->player.dir_x * speed;
		new_y = game->player.y + game->player.dir_y * speed;
		if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->player.key_down)
	{
		new_x = game->player.x - game->player.dir_x * speed;
		new_y = game->player.y - game->player.dir_y * speed;
		if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->player.key_left)
	{
		new_x = game->player.x - game->player.plane_x * speed;
		new_y = game->player.y - game->player.plane_y * speed;
		if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->player.key_right)
	{
		new_x = game->player.x + game->player.plane_x * speed;
		new_y = game->player.y + game->player.plane_y * speed;
		if (game->map.board_with_spaces[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void draw_line(t_player *player, t_game *game, double camera_x, int i)
{
	t_ray *ray = &game->ray;

	// Kierunek promienia (uwzględnia pole widzenia)
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
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

	// Obliczenie dystansu do ściany (zapobieganie dzieleniu przez zero lub bardzo małe wartości)
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;

	// 🔥 Minimalna wartość dystansu, aby uniknąć błędów i "załamania" tekstur
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;

	// Obliczenie wysokości ściany
	int lineHeight = (int)(HEIGHT / ray->perp_wall_dist);

	// Korekta - jeśli linia jest dłuższa niż ekran, rysujemy poprawnie
	int drawStart = -lineHeight / 2 + HEIGHT / 2;
	int drawEnd = lineHeight / 2 + HEIGHT / 2;

	// Jeśli ściana jest wyższa niż ekran, rysowanie zaczyna się powyżej ekranu
	if (drawStart < 0) drawStart = 0;
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

	// Obliczenie współrzędnej X tekstury
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

	// 🔹 Skalowanie tekstury dla bardzo wysokich ścian

	//////////////////////////////////////////////////////////////////////////////////////////// od tego momentu naprawione zostało skalowanie tekstury gdy za blisko ściany
	double step = 1.0 * tex->height / lineHeight;
	double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

	// Rysowanie ściany
	int y = drawStart;
	while (y < drawEnd)
	{
		int tex_y = (int)texPos & (tex->height - 1);  // Zapewnia poprawne indeksowanie tekstury
		texPos += step;

		int tex_offset = (tex_y * tex->size_line) + (ray->tex_x * (tex->bpp / 8));
		int color = *(int *)(tex->data + tex_offset);

		color = apply_fog(color, ray->perp_wall_dist);
		put_pixel(i, y, color, game);
		y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	int			i;
	double		camera_x;

	player = &game->player;
	i = 0;
	move_player(game);
	clear_image(game);
	draw_floor_and_ceiling(game);
	while (i < WIDTH)
	{
		camera_x = 2 * i / (double)WIDTH - 1;
		draw_line(player, game, camera_x, i);
		i++;
	}
	mlx_put_image_to_window(game->window.mlx_ptr,
		game->window.win_ptr, game->window.img, 0, 0);
	return (0);
}

void	set_direction(t_player *player, int dir_x, int dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
	if (dir_x == 0)
	{
		if (dir_y == -1)
			player->plane_x = 0.66;
		else
			player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
	{
		player->plane_x = 0;
		if (dir_x == 1)
			player->plane_y = 0.66;
		else
			player->plane_y = -0.66;
	}
}

void	set_angle(t_game *game)
{
	if (game->player.nswe == 'N')
		set_direction(&game->player, 0, -1);
	else if (game->player.nswe == 'S')
		set_direction(&game->player, 0, 1);
	else if (game->player.nswe == 'E')
		set_direction(&game->player, 1, 0);
	else if (game->player.nswe == 'W')
		set_direction(&game->player, -1, 0);
}

void	player_pos(t_game *game)
{
	char	**mapa;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mapa = game->map.board;
	while (mapa[i])
	{
		j = 0;
		while (mapa[i][j])
		{
			if (mapa[i][j] == 'N' || mapa[i][j] == 'S'
				|| mapa[i][j] == 'E' || mapa[i][j] == 'W')
			{
				game->player.nswe = mapa[i][j];
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
