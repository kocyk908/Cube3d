#include <mlx.h>
#include <stdlib.h>
#include <math.h>
//#include "libft.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
}               t_data;

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(0);
    return (0);
}

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Wolfenstein 3D Clone");
    if (data.win_ptr == NULL)
    {
        free(data.mlx_ptr);
        return (1);
    }

    mlx_hook(data.win_ptr, 17, 0, close_window, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}