#include "game.h"

///////////////////////////////// jakaś funkcja do validacji mapy takiej finalnej, łączenie wszystkiego
// funkcji część jest w map_reading.c

int is_map_valid(t_game game)
{

// czy dobre charactery // is_01SENW
    if (!is_01SENW(game.map.board))
    {
        // trzeba wyczyścić mapę
        printf("Error is_01SENW\n");
        return (0);
    }

// czy 1 gracz //
    if (is_one_player(game.map.board) != 1)
    {
        printf("zla ilosc graczy \n");
        return (0);
    }

    printf("doszło\n");
// czy zamknięta 1-kami //



// czy wystarczająco szeroka / wysoka // is_01SENW do poprawy lub przeniesienia

    

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