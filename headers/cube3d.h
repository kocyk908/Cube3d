#ifndef CUBE3D_H
#define CUBE3D_H

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_next_line.h"
#include "libft.h"

#include "biblio_helper.h"

typedef struct s_window
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_window;

int is_01SENW(char *line);
char **read_map(char *file_path);
void free_map(char **map);
int count_rows(char *file_path);

#endif