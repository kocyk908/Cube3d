/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:23:23 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/20 22:31:10 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	look_for_textures(t_game *game)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (game->map.file[i])
	{
		result = parse_texture_line(game->map.file[i], &game->textures);
		if (result == -1)
		{
			if (game->textures.north_texture != NULL
				&& game->textures.south_texture != NULL
				&& game->textures.west_texture != NULL
				&& game->textures.east_texture != NULL
				&& game->textures.floor_color[0] != -1
				&& game->textures.ceiling_color[0] != -1)
				return (i);
			printf("Error: Invalid line in textures: %s\n", game->map.file[i]);
			return (-1);
		}
		i++;
	}
	return (i);
}

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	int		fd;

	fd = 0;
	if (!path)
	{
		printf("Error: Missing texture file path.\n");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Texture file not found");
		return (0);
	}
	close(fd);
	texture->img = mlx_xpm_file_to_image(game->window.mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load texture from %s\n", path);
		return (0);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_texture(game, &game->textures.north,
			game->textures.north_texture)
		||!load_texture(game, &game->textures.south,
			game->textures.south_texture)
		|| !load_texture(game, &game->textures.west,
			game->textures.west_texture)
		|| !load_texture(game, &game->textures.east,
			game->textures.east_texture))
	{
		printf("Error: Failed to load one or more textures.\n");
		return (0);
	}
	return (1);
}

int	read_textures(t_game *game)
{
	int		line_count;

	line_count = look_for_textures(game);
	if (line_count == -1 || line_count == 0)
	{
		return (0);
	}
	game->textures.height_util = line_count;
	return (1);
}
