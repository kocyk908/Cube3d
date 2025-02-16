/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 15:05:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	has_empty_lines_between(char **map, int height)
{
	int		i;
	int		j;
	int		is_empty;

	i = 1;
	j = 0;
	is_empty = 0;
	while (i < height - 1)
	{
		j = 0;
		is_empty = 1;
		while (map[i][j])
		{
			if (map[i][j] != ' ')
			{
				is_empty = 0;
				break ;
			}
			j++;
		}
		if (is_empty)
			return (1);
		i++;
	}
	return (0);
}

int	is_map_valid(t_game game)
{
	if (!is_01SENW(game.map.board))
	{
		printf("Error is_01SENW\n");
		return (0);
	}
	printf("mapa składa się z dobrych znaków\n\n");
	if (is_one_player(game.map.board) != 1)
	{
		printf("zla ilosc graczy \n");
		return (0);
	}
	printf("jest 1 gracz\n\n");
	if (!is_map_closed(game))
	{
		printf("mapa nie jest zamknięta\n");
		return (0);
	}
	printf("mapa jest zamknięta poprawnie\n\n");
	return (1);
}

int	is_one_player(char **map)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count);
}

int	is_map_closed(t_game game)
{
	if (!is_map_closed_up(game))
	{
		printf("mapa jest otwarta od góry\n");
		return (0);
	}
	if (!is_map_closed_left(game))
	{
		printf("mapa jest otwarta od lewej\n");
		return (0);
	}
	if (!is_map_closed_down(game))
	{
		printf("mapa jest otwarta od dołu\n");
		return (0);
	}
	if (!is_map_closed_right(game))
	{
		printf("mapa jest otwarta od prawej\n");
		return (0);
	}
	return (1);
}
