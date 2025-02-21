/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:41:01 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 13:15:00 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


void	set_direction(t_player *player, int dir_x, int dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
	if (dir_x == 0)
	{
		if (dir_y == -1)
			player->plane_x = 0.66;
		else
			player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
	{
		player->plane_x = 0;
		if (dir_x == 1)
			player->plane_y = 0.66;
		else
			player->plane_y = -0.66;
	}
}

void	set_angle(t_game *game)
{
	if (game->player.nswe == 'N')
		set_direction(&game->player, 0, -1);
	else if (game->player.nswe == 'S')
		set_direction(&game->player, 0, 1);
	else if (game->player.nswe == 'E')
		set_direction(&game->player, 1, 0);
	else if (game->player.nswe == 'W')
		set_direction(&game->player, -1, 0);
}

void	player_pos(t_game *game)
{
	char	**mapa;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mapa = game->map.board;
	while (mapa[i])
	{
		j = 0;
		while (mapa[i][j])
		{
			if (mapa[i][j] == 'N' || mapa[i][j] == 'S'
				|| mapa[i][j] == 'E' || mapa[i][j] == 'W')
			{
				game->player.nswe = mapa[i][j];
				game->player.x = j;
				game->player.y = i;
			}
			j++;
		}
		i++;
	}
	set_angle(game);
	return ;
}
