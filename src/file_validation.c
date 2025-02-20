/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/20 17:10:17 by marvin           ###   ########.fr       */
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

int	parse_texture(char *line, int j, char **texture)
{
	int		len;
	char	*new_texture;

	len = 0;
	new_texture = NULL;
	j += 2;
	while (line[j] == ' ')
		j++;
	new_texture = ft_strdup(&line[j]);
	if (!new_texture)
	{
		printf("Error: Memory allocation failed for texture\n");
		return (0);
	}
	if (*texture)
		free(*texture);
	*texture = new_texture;
	len = ft_strlen(*texture);
	if (len > 0 && (*texture)[len - 1] == '\n')
		(*texture)[len - 1] = '\0';
	return (1);
}

int	util(char *line, int j)
{
	if (line)
	{
		while (line[j] == ' ')
			j++;
	}
	else
		return (0);
	return (j);
}

int	parse_texture_line(char *line, t_textures *textures)
{
	int	j;

	j = util(line, 0);
	if (line[j] == '\0' || line[j] == '\n')
		return (0);
	if (line[j] == 'N' && line[j + 1] == 'O' && line[j + 2] == ' '
		&& textures->north_texture == NULL)
		return (parse_texture(line, j, &textures->north_texture));
	else if (line[j] == 'S' && line[j + 1] == 'O' && line[j + 2] == ' '
		&& textures->south_texture == NULL)
		return (parse_texture(line, j, &textures->south_texture));
	else if (line[j] == 'W' && line[j + 1] == 'E' && line[j + 2] == ' '
		&& textures->west_texture == NULL)
		return (parse_texture(line, j, &textures->west_texture));
	else if (line[j] == 'E' && line[j + 1] == 'A' && line[j + 2] == ' '
		&& textures->east_texture == NULL)
		return (parse_texture(line, j, &textures->east_texture));
	else if (line[j] == 'F' && line[j + 1] == ' '
		&& textures->floor_color[0] == -1)
		return (parse_color(&line[j + 1], textures->floor_color));
	else if (line[j] == 'C' && line[j + 1] == ' '
		&& textures->ceiling_color[0] == -1)
		return (parse_color(&line[j + 1], textures->ceiling_color));
	return (-1);
}

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
