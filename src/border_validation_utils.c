/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:36:04 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/28 10:05:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_map_closed_up(t_game game)
{
	int		i;
	int		j;
	char	**map;
	int		lead_spaces;

	map = map_with_spaces(game);
	lead_spaces = count_leading_spaces(map, game.map.height, game.map.width);
	shift_map_left(map, game.map.height, game.map.width);
	i = 0;
	j = 0;
	while (i < game.map.height - 1 && j < game.map.width - (1 + lead_spaces))
	{
		i = 0;
		while (map[i][j] && i < game.map.height - 1)
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			else if (map[i][j] == '1')
				break ;
			i++;
		}
		j++;
	}
	return (1);
}

int	is_map_closed_left(t_game game)
{
	int		i;
	int		j;
	char	**map;

	map = game.map.board_with_spaces;
	i = 0;
	j = 0;
	while (i < game.map.height - 1 && j < game.map.width - 1)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			else if (map[i][j] == '1')
				break ;
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_closed_down(t_game game)
{
	int		i;
	int		j;
	char	**map;
	int		lead_spaces;

	map = map_with_spaces(game);
	lead_spaces = count_leading_spaces(map, game.map.height, game.map.width);
	shift_map_left(map, game.map.height, game.map.width);
	i = game.map.height - 1;
	j = 0;
	while (i > 0 && j < game.map.width - (1 + lead_spaces))
	{
		i = game.map.height - 1;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			else if (map[i][j] == '1')
				break ;
			i--;
		}
		j++;
	}
	return (1);
}

int	is_map_closed_right(t_game game)
{
	int		i;
	int		j;
	char	**map;

	map = game.map.board_with_spaces;
	i = 0;
	j = game.map.width - 1;
	while (i < game.map.height - 1 && j > 0)
	{
		j = game.map.width - 1;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				return (0);
			else if (map[i][j] == '1')
				break ;
			j--;
		}
		i++;
	}
	return (1);
}
