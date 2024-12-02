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


void print_visited_map(int **visited, int height, int width, int new_x, int new_y)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == new_x && j == new_y)
                printf("\033[1;33m%d \033[0m", visited[i][j]); // Yellow color for the new '1'
            else
                printf("%d ", visited[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}