/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:36:04 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:41:25 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - player->x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - player->y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	}
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
}

void	calculate_line_height_and_draw_positions(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calculate_texture_position(t_ray *ray, t_player *player, t_texture *tex)
{
	if (ray->side == 0)
		ray->wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}
