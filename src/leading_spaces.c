/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leading_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/28 10:07:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	count_leading_spaces(char **map, int height, int width)
{
	int	i;
	int	j;
	int	space_columns;

	j = 0;
	space_columns = 0;
	while (j < width)
	{
		i = 0;
		while (i < height && map[i][j] == ' ')
			i++;
		if (i < height)
			break ;
		space_columns++;
		j++;
	}
	return (space_columns);
}

void	shift_map_left(char **map, int height, int width)
{
	int	shift;
	int	i;
	int	j;

	i = 0;
	j = 0;
	shift = count_leading_spaces(map, height, width);
	if (shift == 0)
		return ;
	while (i < height)
	{
		j = 0;
		while (j < width - shift)
		{
			map[i][j] = map[i][j + shift];
			j++;
		}
		while (j < width)
		{
			map[i][j] = ' ';
			j++;
		}
		map[i][width] = '\0';
		i++;
	}
}
