/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:33:37 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:36:48 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_ray_direction(t_ray *ray, t_player *player, double camera_x)
{
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	set_ray_steps(t_game *game)
{
	t_ray	*ray;

	ray = &game->ray;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0
				- game->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0
				- game->player.y) * ray->delta_dist_y;
	}
}

void	set_ray_direction_and_steps(t_ray *ray, t_player *player, double cam_x)
{
	ray->dir_x = player->dir_x + player->plane_x * cam_x;
	ray->dir_y = player->dir_y + player->plane_y * cam_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}