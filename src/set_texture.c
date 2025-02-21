/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:38:49 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 12:39:04 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_texture	*choose_texture(t_ray *ray, t_textures *textures)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&textures->east);
		else
			return (&textures->west);
	}
	else
	{
		if (ray->step_y > 0)
			return (&textures->south);
		else
			return (&textures->north);
	}
}
