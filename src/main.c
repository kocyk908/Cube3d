#include "window.h"

int close_window(t_window *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(0);
    return (0);
}

int main(void)
{
    t_window  data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Giereczka");
    if (data.win_ptr == NULL)
    {
        free(data.mlx_ptr);
        return (1);
    }

    mlx_hook(data.win_ptr, 17, 0, close_window, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}