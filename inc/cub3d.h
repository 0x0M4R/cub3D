#ifndef CUB3D_H
# define CUB3D_H
//# include "../mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_map
{
	char	**map;
	int		player_pos_x;
	int		player_pos_y;
    int     player_direction;
}	t_map;

void	parse_map(char *filepath, t_map *map);

#endif