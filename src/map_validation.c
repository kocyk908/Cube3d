#include "game.h"

///////////////////////////////// jakaś funkcja do validacji mapy takiej finalnej, łączenie wszystkiego
// część funkcji jest w map_reading.c

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

// sprawdzone zamknięcie góra->dół
int is_map_closed_up(t_game game)
{
    int i;
    int j;
    char **map;

    map = map_with_spaces(game);
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
                break;
            i++;
        }
        j++;
    }
    return (1);
}

// sprawdzone zamknięcie od lewa->prawa
int is_map_closed_left(t_game game)
{
    int i;
    int j;
    char **map;

    map = map_with_spaces(game);
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
                break;
            j++;
        }
        i++;
    }
    return (1);
}

int is_map_closed_down(t_game game)
{
    int i;
    int j;
    char **map;

    map = map_with_spaces(game);
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
                break;
            i--;
        }
        j++;
    }
    return (1);
}

int is_map_closed_right(t_game game)
{
    int i;
    int j;
    char **map;

    map = map_with_spaces(game);
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
                break;
            j--;
        }
        i++;
    }
    return (1);
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