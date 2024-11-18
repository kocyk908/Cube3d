#ifndef WINDOW_H
#define WINDOW_H

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
//#include "libft.h"

typedef struct s_window
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_window;

int close_window(t_window *data);

#endif