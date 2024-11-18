NAME	:= cube3d

CC	:= gcc

CFLAGS	:= -Wall -Wextra -Werror -Iheaders/

MXFLAGS	:= -Lminilibx-linux -lmlx_Linux -lX11 -lXext

SOURCE	:= src/*.c

MLIBX	:= minilibx-linux/

## LIBFT	:= libft/*.c

all:
	make -C $(MLIBX)
	$(CC) $(CFLAGS) $(SOURCE) $(MXFLAGS) -o $(NAME)
##  $(CC) $(CFLAGS) $(SOURCE) $(MXFLAGS) $(LIBFT) -o $(NAME)

clean:
	make clean -C $(MLIBX)
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all