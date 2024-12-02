#include "game.h"

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

// czy wystarczająco szeroka / wysoka //

// to już chyba samo z siebie sie sprawdza

// czy wszystkie 1 są połączone //
    if (!are_all_ones_connected(game))
    {
        printf("nie wszystkie 1 są połączone\n");
        return (0);
    }
    printf("wszystkie 1 są połączone\n\n");

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

/// myślę że trzeba dać że '1' musi miec odok siebie z którejś strony chociaż jedną inną '1'

int is_map_flood_fill(char **map, int x, int y, int height, int width, int **visited)
{
    if (x < 0 || x >= height || y < 0 || y >= width || map[x][y] != '1' || visited[x][y])
        return 0;

    visited[x][y] = 1;

    //print_visited_map(visited, height, width, x, y); // Print the visited map


    is_map_flood_fill(map, x + 1, y, height, width, visited); // south
    is_map_flood_fill(map, x - 1, y, height, width, visited); // north
    is_map_flood_fill(map, x, y + 1, height, width, visited); // east
    is_map_flood_fill(map, x, y - 1, height, width, visited); // west
    is_map_flood_fill(map, x + 1, y + 1, height, width, visited); // south-east
    is_map_flood_fill(map, x - 1, y - 1, height, width, visited); // north-west
    is_map_flood_fill(map, x + 1, y - 1, height, width, visited); // south-west
    is_map_flood_fill(map, x - 1, y + 1, height, width, visited); // north-east

    return 1;
}

int are_all_ones_connected(t_game game)
{
    int **visited;
    int i;
    int j;
    int found_first_one;
    
    found_first_one = 0;
    // allocate visited array
    visited = (int **)malloc(game.map.height * sizeof(int *));
    for (i = 0; i < game.map.height; i++)
    {
        visited[i] = (int *)malloc(game.map.width * sizeof(int));
        for (j = 0; j < game.map.width; j++)
            visited[i][j] = 0;
    }

    // find first '1' and flood fill
    for (i = 0; i < game.map.height && !found_first_one; i++)
    {
        for (j = 0; j < game.map.width && !found_first_one; j++)
        {
            if (game.map.board_with_spaces[i][j] == '1')
            {
                is_map_flood_fill(game.map.board_with_spaces, i, j, game.map.height, game.map.width, visited);
                found_first_one = 1;
            }
        }
    }

    // check if all '1' are connected
    for (i = 0; i < game.map.height; i++)
    {
        for (j = 0; j < game.map.width; j++)
        {
            if (game.map.board_with_spaces[i][j] == '1' && !visited[i][j])
            {
                for (int k = 0; k < game.map.height; k++)
                    free(visited[k]);
                free(visited);
                return 0;
            }
        }
    }

    // free visited array
    for (i = 0; i < game.map.height; i++)
        free(visited[i]);
    free(visited);

    return 1;
}