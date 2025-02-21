/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:48:09 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:49:39 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	init_window(t_game *game)
{
	game->window.mlx_ptr = mlx_init();
	if (game->window.mlx_ptr == NULL)
		return (0);
	game->window.win_ptr = mlx_new_window(game->window.mlx_ptr,
			WIDTH, HEIGHT, "cub3D");
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
