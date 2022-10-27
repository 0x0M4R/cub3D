#ifndef CUB3D_H
# define CUB3D_H
//# include "../mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

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
	int		player_pos_x;
	int		player_pos_y;
	int		player_direction;
	char	*n_texture;
	char	*e_texture;
	char	*s_texture;
	char	*w_texture;
	char	*f_texture;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_map;

void	parse_map(char *filepath, t_map *map);
char	*ft_strjoin(char const *s1, char const *s2);
#endif