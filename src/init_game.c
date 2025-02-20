/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/20 15:07:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <string.h>

int	find_widest_line(char **map)
{
	int		max_width;
	int		current_width;
	int		i;

	i = 0;
	max_width = 0;
	current_width = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		current_width = strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

void	init_map(t_map *map)
{
	map->file_path = NULL;
	map->width = 0;
	map->height = 0;
	map->file = NULL;
	map->board = NULL;
	map->board_with_spaces = NULL;
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

void	init_textures_util(t_texture *direction)
{
	direction->img = NULL;
	direction->data = NULL;
	direction->width = 0;
	direction->height = 0;
	direction->bpp = 0;
	direction->size_line = 0;
	direction->endian = 0;
}

void	init_textures(t_textures *textures)
{
	init_textures_util(&textures->north);
	init_textures_util(&textures->south);
	init_textures_util(&textures->west);
	init_textures_util(&textures->east);
	textures->north_texture = NULL;
	textures->south_texture = NULL;
	textures->west_texture = NULL;
	textures->east_texture = NULL;
	textures->floor_color[0] = -1;
	textures->ceiling_color[0] = -1;
	textures->floor_color[1] = -1;
	textures->ceiling_color[1] = -1;
	textures->floor_color[2] = -1;
	textures->ceiling_color[2] = -1;
	textures->final_floor_color = -1;
	textures->final_ceiling_color = -1;
	textures->height_util = 0;
}

int	init_window(t_game *game)
{
	game->window.mlx_ptr = mlx_init();
	if (game->window.mlx_ptr == NULL)
		return (0);
	game->window.win_ptr = mlx_new_window(game->window.mlx_ptr,
			WIDTH, HEIGHT, "Giereczka");
	if (game->window.win_ptr == NULL)
	{
		free(game->window.mlx_ptr);
		return (0);
	}
	game->window.img = mlx_new_image(game->window.mlx_ptr, WIDTH, HEIGHT);
	if (game->window.img == NULL)
	{
		free(game->window.img);
		return (0);
	}
	game->window.data = mlx_get_data_addr(game->window.img, &game->window.bpp,
			&game->window.size_l, &game->window.endian);
	mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr,
		game->window.img, 0, 0);
	return (1);
}
// Funkcja alokująca map

int	init_game(t_game *game)
{
	init_map(&game->map);
	init_player(&game->player);
	init_textures(&game->textures);
	return (1);
}
