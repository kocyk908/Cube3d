/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/20 12:35:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_map(char **map)
{
	int		i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_textures(t_game *game)
{
	if (game->textures.north.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.south.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.west.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->window.mlx_ptr, game->textures.east.img);
	if (game->textures.north_texture)
		free(game->textures.north_texture);
	if (game->textures.south_texture)
		free(game->textures.south_texture);
	if (game->textures.west_texture)
		free(game->textures.west_texture);
	if (game->textures.east_texture)
		free(game->textures.east_texture);
}

void	free_game_resources(t_game *game)
{
	if (game->map.board)
		free_map(game->map.board);
	if (game->map.board_with_spaces)
		free_map(game->map.board_with_spaces);
	if (game->map.file)
		free_map(game->map.file);
	free_textures(game);
	if (game->window.mlx_ptr)
	{
		if (game->window.win_ptr)
		{
			mlx_clear_window(game->window.mlx_ptr, game->window.win_ptr);
			mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
		}
		if (game->window.img)
			mlx_destroy_image(game->window.mlx_ptr, game->window.img);
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
	}
}
