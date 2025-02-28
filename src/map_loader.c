/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:30:09 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/28 08:45:25 by marvin           ###   ########.fr       */
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
	game->map.height = count_rows_map(game->map.board);
	game->map.width = find_longest_row_length(game->map.board);
	player_pos(game);
	if (!is_map_valid(*game))
	{
		free_game_resources(game);
		return (printf("Error: Invalid map\n"), 0);
	}
	return (1);
}
