/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/21 13:15:37 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	key_pressed(int command, t_game *game)
{
	if (command == W)
		game->player.key_up = true;
	else if (command == S)
		game->player.key_down = true;
	else if (command == A)
		game->player.key_left = true;
	else if (command == D)
		game->player.key_right = true;
	if (command == LEFT)
		game->player.left_rotate = true;
	else if (command == RIGHT)
		game->player.right_rotate = true;
	else if (command == 65307)
	{
		close_window(game);
		exit(0);
	}
	return (0);
}

int	key_release(int command, t_game *game)
{
	if (command == W)
		game->player.key_up = false;
	else if (command == S)
		game->player.key_down = false;
	else if (command == A)
		game->player.key_left = false;
	else if (command == D)
		game->player.key_right = false;
	if (command == LEFT)
		game->player.left_rotate = false;
	else if (command == RIGHT)
		game->player.right_rotate = false;
	return (0);
}
