#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;
typedef struct s_map
{
	char	**map;
	t_mlx	mlx;
	int		player_pos_x;
	int		player_pos_y;
	int		player_direction;
	char	*n_texture;
	char	*e_texture;
	char	*s_texture;
	char	*w_texture;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_map;

void	parse_map(char *filepath, t_map *map);

int		parse_elements(t_map *map, char *content);

#endif