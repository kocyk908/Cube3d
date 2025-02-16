/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 22:51:17 by marvin           ###   ########.fr       */
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

int	load_floor(t_game *game)
{
	int		color;

	color = rgb_to_hex(game->textures.floor_color[0],
			game->textures.floor_color[1], game->textures.floor_color[2]);
	return (color);
}

int	load_ceiling(t_game *game)
{
	int		color;

	color = rgb_to_hex(game->textures.ceiling_color[0],
			game->textures.ceiling_color[1], game->textures.ceiling_color[2]);
	return (color);
}

void	draw_floor_and_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		floor_ceiling[2];
	double	distance;
	int		color;

	x = 0;
	floor_ceiling[0] = load_floor(game);
	floor_ceiling[1] = load_ceiling(game);
	while (x < HEIGHT)
	{
		y = 0;
		distance = HEIGHT / (2.0 * x - HEIGHT);
		if (x < HEIGHT / 2)
			color = floor_ceiling[1];
		else
			color = floor_ceiling[0];
		color = apply_fog(color, distance);
		while (y < WIDTH)
		{
			put_pixel(y, x, color, game);
			y++;
		}
		x++;
	}
}
