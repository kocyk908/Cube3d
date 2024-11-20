#ifndef WINDOW_H
#define WINDOW_H

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_next_line.h"
#include "libft.h"

typedef struct s_window
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_window;

int is_valid_line(char *line);
char **read_map(char *file_path);
void free_map(char **map);

#endif