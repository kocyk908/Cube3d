/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 17:50:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	apply_fog(int color, double distance)
{
	double	fog_factor;
	int		r;
	int		g;
	int		b;

	fog_factor = exp(-distance * 0.05);
	if (fog_factor > 1.0)
		fog_factor = 1.0;
	if (fog_factor < 0.1)
		fog_factor = 0.1;
	r = ((color >> 16) & 0xFF) * fog_factor;
	g = ((color >> 8) & 0xFF) * fog_factor;
	b = (color & 0xFF) * fog_factor;
	return ((r << 16) | (g << 8) | b);
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_floor_and_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		floor_base;
	int		ceiling_base;
	double	distance;
	int		color;

	floor_base = rgb_to_hex(game->textures.floor_color[0], game->textures.floor_color[1], game->textures.floor_color[2]);
	ceiling_base = rgb_to_hex(game->textures.ceiling_color[0], game->textures.ceiling_color[1], game->textures.ceiling_color[2]);
	for (y = 0; y < HEIGHT; y++)
	{
		distance = HEIGHT / (2.0*y - HEIGHT);
		color = (y < HEIGHT / 2) ? ceiling_base : floor_base;
		color = apply_fog(color, distance);
		for (x = 0; x < WIDTH; x++)
			put_pixel(x, y, color, game);
	}
}
