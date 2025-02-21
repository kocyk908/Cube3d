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
