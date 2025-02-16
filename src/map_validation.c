/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 13:35:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int has_empty_lines_between(char **map, int height)
{
    int i;

    for (i = 1; i < height - 1; i++) // Skip the first and last lines
    {
        // Check if the line is empty or contains only spaces
        int j = 0;
        int is_empty = 1;
        while (map[i][j])
        {
            if (map[i][j] != ' ')
            {
                is_empty = 0; // Found a non-space character
                break;
            }
            j++;
        }
        if (is_empty)
            return (1); // Found an empty or whitespace-only line
    }
    return (0); // No empty lines found
}








int is_map_valid(t_game game)
{

// czy dobre charactery // is_01SENW
    if (!is_01SENW(game.map.board))
    {
        // trzeba wyczyścić mapę
        printf("Error is_01SENW\n");
        return (0);
    }
    printf("mapa składa się z dobrych znaków\n\n");

// czy 1 gracz //
    if (is_one_player(game.map.board) != 1)
    {
        printf("zla ilosc graczy \n");
        return (0);
    }
    printf("jest 1 gracz\n\n");

// czy zamknięta 1-kami //
    if (!is_map_closed(game))
    {
        printf("mapa nie jest zamknięta\n");
        return (0);
    }
    printf("mapa jest zamknięta poprawnie\n\n");

// czy są puste linie //
    //if (has_empty_lines_between(game.map.board_with_spaces, game.map.height))
    //{
    //    printf("są puste linie\n");
    //    return (0);
    //}
    //printf("nie ma pustych linii\n\n");
// czy wystarczająco szeroka / wysoka //

// to już chyba samo z siebie sie sprawdza

// czy wszystkie 1 są połączone //
    //if (!are_all_ones_connected(game))
    //{
    //    printf("nie wszystkie 1 są połączone\n");
    //    return (0);
    //}
    //printf("wszystkie 1 są połączone\n\n");

    return (1);
}

int is_one_player(char **map)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
	i = 0;
    j = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                player_count++;
            }
            j++;
        }
        i++;
    }
    return (player_count);
}

int is_map_closed(t_game game)
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