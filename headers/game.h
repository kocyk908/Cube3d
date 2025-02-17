/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:42 by lkoc              #+#    #+#             */
/*   Updated: 2025/02/16 13:39:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 720

# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# define SPEED 0.05

# include "cube3d.h"

typedef struct s_player
{
	double		x; // Pozycja X gracza
	double		y; // Pozycja Y gracza
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
	double		plane_x;
	double		plane_y; // Wektor kamery (perspektywa FOV)
	double		dir_x; // Kierunek X
	double		dir_y; // Kierunek Y
	char		nswe;
}				t_player;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y; // Kierunek promienia
	int			map_x;
	int			map_y; // Aktualna pozycja w siatce mapy
	double		side_dist_x;
	double		side_dist_y; // Odległości do kolejnych ścian
	double		delta_dist_x;
	double		delta_dist_y; // Różnice między kolejnymi skokami w osi X i Y
	double		perp_wall_dist; // Odległość do ściany
	int			step_x;
	int			step_y; // Kierunek kroków DDA
	int			hit; // Czy promień trafił w ścianę?
	int			side; // 0 = pionowa ściana, 1 = pozioma ściana
	double		wall_x; // Pozycja uderzenia w ścianę (do teksturowania)
	int			tex_x; // Współrzędna X tekstury
}				t_ray;

typedef struct s_map
{
	char		*file_path; // Ścieżka do pliku z mapą
	int			width;
	int			height;
	char		**file;
	char		**board; // Reprezentacja mapy (np. tablica znaków '1', '0')
	char		**board_with_spaces;
}				t_map;

typedef struct s_texture
{
	void		*img; // Wskaźnik obrazu MLX
	char		*data; // Surowe dane obrazu (piksele)
	int			width; // Szerokość tekstury
	int			height; // Wysokość tekstury
	int			bpp; // Bity na piksel
	int			size_line; // Rozmiar linii (w bajtach)
	int			endian; // Kolejność bajtów
}				t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3]; // RGB dla F
	int			ceiling_color[3]; // RGB dla C
	double		final_floor_color;
	double		final_ceiling_color;
	int			height_util; // Liczba linii wczytanych przez GNL dla tekstur i kolorów (pozostale powinny być dla mapy)
}				t_textures;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;

	char		*data;
	int			bpp;
	int			size_l;
	int			endian;
}				t_window;

typedef struct s_game
{
	t_ray			ray;
	t_window		window; // Dane okna MLX
	t_player		player; // Dane gracza
	t_map			map; // Dane mapy
	t_textures		textures; // Dane tekstur
}				t_game;

// Prototypy funkcji
int		init_game(t_game *game);
int		init_window(t_game *game);
void	init_map(t_map *map);
int		close_window(t_game *game);
char	**map_with_spaces(t_game game);
int		is_map_valid(t_game game);
int		is_one_player(char **map);
int		is_map_closed(t_game game);
int		find_longest_row_length(char **map);
int		is_map_closed_up(t_game game);
int		is_map_closed_left(t_game game);
int		is_map_closed_down(t_game game);
int		is_map_closed_right(t_game game);

int		are_all_ones_connected(t_game game);

int		read_textures(t_game *game);
int		ft_isspace(char c);

char	**read_map(t_game *game);
char	**read_file(char *file_path);

void	player_pos(t_game *game);

// FUNKCJE Z FILMU
void	draw_square(int x, int y, int size, int color, t_game *game);
int		key_pressed(int command, t_game *game);
int		key_release(int command, t_game *game);
int		draw_loop(t_game *game);
void	clear_image(t_game *game);
void	draw_map(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);

void	load_textures(t_game *game);

void	calculate_texture(t_game *game);
void	perform_dda(t_game *game);
void	draw_floor_and_ceiling(t_game *game);
int		apply_fog(int color, double distance);
int		rgb_to_int(int r, int g, int b);

#endif
