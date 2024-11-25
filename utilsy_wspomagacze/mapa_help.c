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
        for (int j = 0; map[i][j]; j++)
        {
            printf("%i ", map[i][j]);
        }
        printf("\n");
    }
    
}