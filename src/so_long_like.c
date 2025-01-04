#include "game.h"



int key_pressed(int command, t_game *game)
{
	//printf("controls working command -> %i\n", command);
    if (command == W) // Strzałka w górę
        game->player.key_up = true;
	else if (command == S)
		game->player.key_down = true;
	else if (command == A)
		game->player.key_left = true;
	else if (command == D)
		game->player.key_right = true;
    if (command == LEFT)
        game->player.left_rotate = true;
    else if (command == RIGHT)
        game->player.right_rotate = true;
    return (0);

}

int key_release(int command, t_game *game)
{
    if (command == W)
        game->player.key_up = false;
	else if (command == S)
		game->player.key_down = false;
	else if (command == A)
		game->player.key_left = false;
	else if (command == D)
		game->player.key_right = false;
    if (command == LEFT)
        game->player.left_rotate = false;
    else if (command == RIGHT)
        game->player.right_rotate = false;
    return (0);
}