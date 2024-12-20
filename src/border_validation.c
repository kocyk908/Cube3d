#include "game.h"

// sprawdzone zamknięcie góra->dół
int is_map_closed_up(t_game game)
{
    int i;
    int j;
    char **map;

    map = map_with_spaces(game);
    print_map(map);
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

