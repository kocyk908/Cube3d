NAME	:= cub3D

CC	:= gcc

CFLAGS	:= -Wall -Wextra -Werror -Iheaders/

MXFLAGS	:= -Lminilibx-linux -lmlx_Linux -lm -lX11 -lXext

SOURCE	:= src/border_validation.c src/calculate.c src/close_window.c src/dda.c src/draw.c src/file_validation.c src/fog.c src/free_utils.c src/init_game.c src/init_map.c src/init_player.c src/init_textures.c src/init_window.c src/keys.c src/main.c src/map_loader.c src/map_reading.c src/map_utils.c src/map_validation.c src/player_movement.c src/render_game.c src/set_dir.c src/set_raycasting.c src/set_texture.c src/texture_loading.c src/utils.c

MLIBX	:= minilibx-linux/

LIBFT	:= libft/*.c

GNL := gnl/*.c

all:
	make -C $(MLIBX)
	$(CC) $(CFLAGS) $(SOURCE) $(GNL) $(LIBFT) $(MXFLAGS) -o $(NAME)

clean:
	make clean -C $(MLIBX)
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all