/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 22:54:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int		index;

	index = 0;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->window.size_l + x * (game->window.bpp / 8);
	game->window.data[index] = color & 0xFF;
	game->window.data[index + 1] = (color >> 8) & 0xFF;
	game->window.data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_pixel(i, j, 0, game);
			j++;
		}
		i++;
	}
}
