#include "biblio_helper.h"

void print_map(char **map)
{
    if (!map)
    {
        printf("Map is empty or NULL.\n");
        return;
    }
    
    for (int i = 0; map[i]; i++)
    {
        printf("%s", map[i]); // Każda linia mapy zawiera znak '\n', więc nie dodajemy dodatkowego '\n'
    }
}