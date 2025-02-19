/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/19 23:16:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	invalid_char(char *line, int j)
{
	while (line[j] != '\0' && line[j] != '\n')
	{
		if (!ft_isdigit(line[j]) && line[j] != ',' && !ft_isspace(line[j]))
		{
			printf("Error: Invalid character in floor: '%c'\n", line[j]);
			return (1);
		}
		j++;
	}
	return (0);
}

int	parse_color(char *line, int *color)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (line[j] == ' ')
		j++;
	if (invalid_char(line, j))
		return (0);
	k = 0;
	while (k < 3)
	{
		color[k] = ft_atoi(&line[j]);
		while (line[j] != ',' && line[j] != '\0')
			j++;
		if (line[j] == ',')
		{
			j++;
			while (line[j] == ' ')
				j++;
		}
		k++;
	}
	return (1);
}

void	free_textures(t_game *game)
{
	// Free MinilibX images if they were allocated
	if (game->textures.north.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.south.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.west.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.east.img);

	// Free texture paths (from `ft_strdup()`)
	if (game->textures.north_texture)
		free(game->textures.north_texture);
	if (game->textures.south_texture)
		free(game->textures.south_texture);
	if (game->textures.west_texture)
		free(game->textures.west_texture);
	if (game->textures.east_texture)
		free(game->textures.east_texture);
}

int	parse_texture(char *line, int j, char **texture)
{
	int		len;
	char	*new_texture;

	j += 2;
	while (line[j] == ' ')
		j++;

	new_texture = ft_strdup(&line[j]); // Store in a temporary variable
	if (!new_texture)
	{
		printf("Error: Memory allocation failed for texture\n");
		return (0);
	}

	// Free the old texture before assigning a new one
	if (*texture)
		free(*texture);

	*texture = new_texture;

	len = ft_strlen(*texture);
	if (len > 0 && (*texture)[len - 1] == '\n')
		(*texture)[len - 1] = '\0';

	return (1);
}


int	look_for_textures(t_game *game)
{
	int		i;
	int		j;
	char	**file;

	file = game->map.file;
	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ')
			j++;
		if (file[i][j] == '\0' || file[i][j] == '\n')
		{
			i++;
			continue ;
		}
		if (file[i][j] == 'N' && file[i][j + 1] == 'O' && file[i][j + 2] == ' ' && game->textures.north_texture == NULL)
		{
			if (!parse_texture(file[i], j, &game->textures.north_texture))
				return (-1);
		}
		else if (file[i][j] == 'S' && file[i][j + 1] == 'O' && file[i][j + 2] == ' ' && game->textures.south_texture == NULL)
		{
			if (!parse_texture(file[i], j, &game->textures.south_texture))
				return (-1);
		}
		else if (file[i][j] == 'W' && file[i][j + 1] == 'E' && file[i][j + 2] == ' ' && game->textures.west_texture == NULL)
		{
			if (!parse_texture(file[i], j, &game->textures.west_texture))
				return (-1);
		}
		else if (file[i][j] == 'E' && file[i][j + 1] == 'A' && file[i][j + 2] == ' ' && game->textures.east_texture == NULL)
		{
			if (!parse_texture(file[i], j, &game->textures.east_texture))
				return (-1);
		}
		else if (file[i][j] == 'F' && file[i][j + 1] == ' ' && game->textures.floor_color[0] == -1)
		{
			j++;
			if (!parse_color(&file[i][j], game->textures.floor_color))
				return (-1);
		}
		else if (file[i][j] == 'C' && file[i][j + 1] == ' ' && game->textures.ceiling_color[0] == -1)
		{
			j++;
			if (!parse_color(&file[i][j], game->textures.ceiling_color))
				return (-1);
		}
		else
		{
			if (game->textures.north_texture != NULL && game->textures.south_texture != NULL && game->textures.west_texture != NULL && game->textures.east_texture != NULL && game->textures.floor_color[0] != -1 && game->textures.ceiling_color[0] != -1)
				return (i);
			printf("Error: Invalid line in textures: %s or those are not textures\n ", file[i]);
			return (-1);
		}
		i++;
	}
	return (i);
}

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	int fd;

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
	texture->img = mlx_xpm_file_to_image(game->window.mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load texture from %s\n", path);
		return (0);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
	return (1);
}


int	load_textures(t_game *game)
{
	if (!load_texture(game, &game->textures.north, game->textures.north_texture) ||
		!load_texture(game, &game->textures.south, game->textures.south_texture) ||
		!load_texture(game, &game->textures.west, game->textures.west_texture) ||
		!load_texture(game, &game->textures.east, game->textures.east_texture))
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
