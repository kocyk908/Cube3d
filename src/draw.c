/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:39:23 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:41:25 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_line_segment(t_game *game, int i)
{
	t_texture	*tex;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			color;

	tex = choose_texture(&game->ray, &game->textures);
	tex_pos = (game->ray.draw_start - HEIGHT / 2 + game->ray.line_height / 2)
		* (1.0 * tex->height / game->ray.line_height);
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		tex_y = ((int)tex_pos) & (tex->height - 1);
		tex_pos += (1.0 * tex->height / game->ray.line_height);
		color = *(int *)(tex->data + ((tex_y * tex->size_line)
					+ (game->ray.tex_x * (tex->bpp / 8))));
		color = apply_fog(color, game->ray.perp_wall_dist);
		put_pixel(i, y, color, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, double camera_x, int i)
{
	t_texture	*tex;

	set_ray_direction_and_steps(&game->ray, player, camera_x);
	set_ray_steps(game);
	perform_dda(game);
	calculate_wall_distance(&game->ray, player);
	calculate_line_height_and_draw_positions(&game->ray);
	tex = choose_texture(&game->ray, &game->textures);
	calculate_texture_position(&game->ray, player, tex);
	draw_line_segment(game, i);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	int			i;
	double		camera_x;

	player = &game->player;
	i = 0;
	move_player(game);
	clear_image(game);
	draw_floor_and_ceiling(game);
	while (i < WIDTH)
	{
		camera_x = 2 * i / (double)WIDTH - 1;
		draw_line(player, game, camera_x, i);
		i++;
	}
	mlx_put_image_to_window(game->window.mlx_ptr,
		game->window.win_ptr, game->window.img, 0, 0);
	return (0);
}
