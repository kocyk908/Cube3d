/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:33:02 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:36:47 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void	move_in_direction(t_player *player, t_map *map,
		double move_x, double move_y)
{
	if (map->board_with_spaces[(int)(player->y + move_y)]
		[(int)(player->x + move_x)] != '1')
	{
		player->x += move_x;
		player->y += move_y;
	}
}

void	move_player(t_game *game)
{
	double	speed;
	double	angle_speed;

	speed = SPEED;
	angle_speed = 0.05;
	if (game->player.right_rotate)
		rotate_player(&game->player, angle_speed);
	if (game->player.left_rotate)
		rotate_player(&game->player, -angle_speed);
	if (game->player.key_up)
		move_in_direction(&game->player, &game->map, game->player.dir_x
			* speed, game->player.dir_y * speed);
	if (game->player.key_down)
		move_in_direction(&game->player, &game->map, -game->player.dir_x
			* speed, -game->player.dir_y * speed);
	if (game->player.key_left)
		move_in_direction(&game->player, &game->map, -game->player.plane_x
			* speed, -game->player.plane_y * speed);
	if (game->player.key_right)
		move_in_direction(&game->player, &game->map, game->player.plane_x
			* speed, game->player.plane_y * speed);
}
