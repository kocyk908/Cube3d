/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/28 10:05:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// Rekurencyjny DFS do sprawdzania, czy gracz może dotrzeć do granicy mapy
void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (map[x][y] == '1' || map[x][y] == 'V')
	{
		return ;
	}
	map[x][y] = 'V';
	if (x <= 0 || y <= 0 || x >= game->map.height - 1
		|| y >= game->map.width - 1)
	{
		game->map.error_border = 1;
		return ;
	}
	if (game->map.error_border == 1)
	{
		return ;
	}
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x, y - 1, game);
	flood_fill(map, x, y + 1, game);
}

// Funkcja sprawdzająca, czy mapa jest poprawnie zamknięta
int	is_map_closed(t_game *game, char **map)
{
	int		i;
	int		j;

	i = 0;
	game->map.error_border = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (map[i][j] == game->player.nswe)
			{
				flood_fill(map, i, j, game);
				if (game->map.error_border == 1)
					return (0);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	are_borders_valid(t_game game)
{
	if (!is_map_closed_left(game))
	{
		printf("Map is not closed left\n");
		return (0);
	}
	if (!is_map_closed_up(game))
	{
		printf("Map is not closed up\n");
		return (0);
	}
	if (!is_map_closed_down(game))
	{
		printf("Map is not closed down\n");
		return (0);
	}
	if (!is_map_closed_right(game))
	{
		printf("Map is not closed right\n");
		return (0);
	}
	return (1);
}
