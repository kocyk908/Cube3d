/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:04:42 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/21 13:04:48 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	find_widest_line(char **map)
{
	int		max_width;
	int		current_width;
	int		i;

	i = 0;
	max_width = 0;
	current_width = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		current_width = strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

void	init_map(t_map *map)
{
	map->file_path = NULL;
	map->width = 0;
	map->height = 0;
	map->file = NULL;
	map->board = NULL;
	map->board_with_spaces = NULL;
}
