/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:00:45 by bkaleta           #+#    #+#             */
/*   Updated: 2025/02/24 14:00:45 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "biblio_helper.h"

// void	print_map(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!map)
// 	{
// 		printf("Map is empty or NULL.\n");
// 		return ;
// 	}
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			printf("%i ", map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// void	print_visited_map(int **visited,
// 			int height, int width, int new_x, int new_y)
// {
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             if (i == new_x && j == new_y)
//                 printf("\033[1;33m%d \033[0m", visited[i][j]);
//             else
//                 printf("%d ", visited[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }