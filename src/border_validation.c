/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/27 19:58:42 by lkoc             ###   ########.fr       */
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
int	is_map_closed(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = game->map.board_with_spaces;
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
