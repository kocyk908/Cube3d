/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:05:04 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 13:05:09 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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
