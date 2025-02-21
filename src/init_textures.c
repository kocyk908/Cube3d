/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:51:04 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:51:11 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_textures_util(t_texture *direction)
{
	direction->img = NULL;
	direction->data = NULL;
	direction->width = 0;
	direction->height = 0;
	direction->bpp = 0;
	direction->size_line = 0;
	direction->endian = 0;
}

void	init_textures(t_textures *textures)
{
	init_textures_util(&textures->north);
	init_textures_util(&textures->south);
	init_textures_util(&textures->west);
	init_textures_util(&textures->east);
	textures->north_texture = NULL;
	textures->south_texture = NULL;
	textures->west_texture = NULL;
	textures->east_texture = NULL;
	textures->floor_color[0] = -1;
	textures->ceiling_color[0] = -1;
	textures->floor_color[1] = -1;
	textures->ceiling_color[1] = -1;
	textures->floor_color[2] = -1;
	textures->ceiling_color[2] = -1;
	textures->final_floor_color = -1;
	textures->final_ceiling_color = -1;
	textures->height_util = 0;
}
