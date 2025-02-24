/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/24 22:39:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_map_closed_up(t_game game)
{
	int		i;
	int		j;
	char	**map;

	map = game.map.board_with_spaces;
	i = 0;
	j = 0;
	while (i < game.map.height - 1 && j < game.map.width - 1)
	{
		i = 0;
		while (map[i][j])
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

	map = game.map.board_with_spaces;
	i = game.map.height - 1;
	j = 0;
	while (i > 0 && j < game.map.width - 1)
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
