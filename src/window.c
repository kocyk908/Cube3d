/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 13:36:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "cube3d.h"

int close_window(t_game *game)
{
    if (game->window.win_ptr)
        mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
    if (game->window.mlx_ptr)
        free(game->window.mlx_ptr);
    exit(0);
    return (0);
}
