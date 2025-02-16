/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 22:26:43 by marvin           ###   ########.fr       */
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

	j += 2;
	while (line[j] == ' ')
		j++;
	*texture = ft_strdup(&line[j]);
	len = ft_strlen(*texture);
	if (len > 0 && (*texture)[len - 1] == '\n')
		(*texture)[len - 1] = '\0';
	if (*texture == NULL)
	{
		printf("Error: Memory allocation failed for texture\n");
		return (0);
	}
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

void	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->window.mlx_ptr,
			path, &texture->width, &texture->height);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->textures.north, game->textures.north_texture);
	load_texture(game, &game->textures.south, game->textures.south_texture);
	load_texture(game, &game->textures.west, game->textures.west_texture);
	load_texture(game, &game->textures.east, game->textures.east_texture);
}

int	read_textures(t_game *game)
{
	int		line_count;

	line_count = look_for_textures(game);
	if (line_count == -1)
	{
		return (0);
	}
	game->textures.height_util = line_count;
	return (1);
}
