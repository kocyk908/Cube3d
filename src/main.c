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

int	validate_and_load_map(t_game *game, char *file_path)
{
	game->map.file_path = file_path;
	if (ft_strcmp(&file_path[ft_strlen(file_path) - 4], ".cub") != 0)
		return (printf("Error: Invalid file extension\n"), 0);
	game->map.file = read_file(file_path);
	if (!game->map.file)
	{
		printf("Error: Failed to read file\n");
		return (0);
	}
	if (!read_textures(game))
	{
		free_game_resources(game);
		return (printf("Error: Failed to read textures\n"), 0);
	}
	game->map.board = read_map(game);
	game->map.board_with_spaces = map_with_spaces(*game);
	game->map.width = find_longest_row_length(game->map.board);
	game->map.height = game->textures.height_util;
	if (!is_map_valid(*game))
	{
		free_game_resources(game);
		return (printf("Error: Invalid map\n"), 0);
	}
	player_pos(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Usage: %s <map_file>\n", argv[0]), 1);
	init_game(&game);
	if (!validate_and_load_map(&game, argv[1]))
		return (0);
	if (!init_window(&game))
	{
		free_game_resources(&game);
		return (1);
	}
	if (!load_textures(&game))
	{
		free_game_resources(&game);
		return (1);
	}
	mlx_hook(game.window.win_ptr, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.window.win_ptr, 3, 1L << 1, key_release, &game);
	mlx_hook(game.window.win_ptr, 17, 0, close_window, &game);
	mlx_loop_hook(game.window.mlx_ptr, draw_loop, &game);
	mlx_loop(game.window.mlx_ptr);
	free_game_resources(&game);
	return (0);
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void	move_in_direction(t_player *player, t_map *map,
		double move_x, double move_y)
{
	if (map->board_with_spaces[(int)(player->y + move_y)]
		[(int)(player->x + move_x)] != '1')
	{
		player->x += move_x;
		player->y += move_y;
	}
}

void	move_player(t_game *game)
{
	double	speed;
	double	angle_speed;

	speed = SPEED;
	angle_speed = 0.05;
	if (game->player.right_rotate)
		rotate_player(&game->player, angle_speed);
	if (game->player.left_rotate)
		rotate_player(&game->player, -angle_speed);
	if (game->player.key_up)
		move_in_direction(&game->player, &game->map, game->player.dir_x
			* speed, game->player.dir_y * speed);
	if (game->player.key_down)
		move_in_direction(&game->player, &game->map, -game->player.dir_x
			* speed, -game->player.dir_y * speed);
	if (game->player.key_left)
		move_in_direction(&game->player, &game->map, -game->player.plane_x
			* speed, -game->player.plane_y * speed);
	if (game->player.key_right)
		move_in_direction(&game->player, &game->map, game->player.plane_x
			* speed, game->player.plane_y * speed);
}

void	set_ray_direction(t_ray *ray, t_player *player, double camera_x)
{
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	set_ray_steps(t_game *game)
{
	t_ray	*ray;

	ray = &game->ray;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0
				- game->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0
				- game->player.y) * ray->delta_dist_y;
	}
}

void	set_ray_direction_and_steps(t_ray *ray, t_player *player, double cam_x)
{
	ray->dir_x = player->dir_x + player->plane_x * cam_x;
	ray->dir_y = player->dir_y + player->plane_y * cam_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - player->x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - player->y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	}
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
}

void	calculate_line_height_and_draw_positions(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calculate_texture_position(t_ray *ray, t_player *player, t_texture *tex)
{
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
}

t_texture	*choose_texture(t_ray *ray, t_textures *textures)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&textures->east);
		else
			return (&textures->west);
	}
	else
	{
		if (ray->step_y > 0)
			return (&textures->south);
		else
			return (&textures->north);
	}
}

//void	draw_line_segment(t_game *game, int i)
//{
//	t_texture	*tex;
//	double		tex_pos;
//	int			y;
//	int			tex_y;
//	int			color;
//	int		tex_offset;

//	tex = choose_texture(&game->ray, &game->textures);
//	tex_pos = (game->ray.draw_start - HEIGHT / 2 + game->ray.line_height / 2)
//		* (1.0 * tex->height / game->ray.line_height);
//	y = game->ray.draw_start;
//	while (y < game->ray.draw_end)
//	{
//		tex_y = ((int)tex_pos) & (tex->height - 1);
//		tex_pos += (1.0 * tex->height / game->ray.line_height);
//		tex_offset = (tex_y * tex->size_line)
//			+ (game->ray.tex_x * (tex->bpp / 8));
//		color = *(int *)(tex->data + tex_offset);
//		color = apply_fog(color, game->ray.perp_wall_dist);
//		put_pixel(i, y, color, game);
//		y++;
//	}
//}

void	draw_line_segment(t_game *game, int i)
{
	t_texture	*tex;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			color;

	tex = choose_texture(&game->ray, &game->textures);
	tex_pos = (game->ray.draw_start - HEIGHT / 2 + game->ray.line_height / 2)
		* (1.0 * tex->height / game->ray.line_height);
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		tex_y = ((int)tex_pos) & (tex->height - 1);
		tex_pos += (1.0 * tex->height / game->ray.line_height);
		color = *(int *)(tex->data + ((tex_y * tex->size_line)
					+ (game->ray.tex_x * (tex->bpp / 8))));
		color = apply_fog(color, game->ray.perp_wall_dist);
		put_pixel(i, y, color, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, double camera_x, int i)
{
	t_texture	*tex;

	set_ray_direction_and_steps(&game->ray, player, camera_x);
	set_ray_steps(game);
	perform_dda(game);
	calculate_wall_distance(&game->ray, player);
	calculate_line_height_and_draw_positions(&game->ray);
	tex = choose_texture(&game->ray, &game->textures);
	calculate_texture_position(&game->ray, player, tex);
	draw_line_segment(game, i);
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
