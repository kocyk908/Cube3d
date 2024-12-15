#ifndef CUBE3D_H
#define CUBE3D_H

#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_next_line.h"
#include "libft.h"
#include "stdbool.h"

#include "biblio_helper.h"

int is_01SENW(char **map);
void free_map(char **map);
int count_rows(char *file_path);

#endif