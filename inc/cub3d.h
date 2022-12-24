/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:47:46 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/24 19:20:15 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*tmp;
}	t_mlx;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_ixy
{
	int		x;
	int		y;
}	t_ixy;

typedef struct s_dxy
{
	double	x;
	double	y;
}	t_dxy;
typedef struct s_render
{
	int		height;
}	t_render;

typedef struct s_player
{
	double		angle;
	t_dxy		pos;
	t_ixy		map;
	t_render	render;
}	t_player;

typedef struct s_map
{
	char		**map;
	t_mlx		mlx;
	t_player	player;
	double		time;
	double		old_time;
	int			player_direction;
	char		*n_texture;
	char		*e_texture;
	char		*s_texture;
	char		*w_texture;
	t_rgb		floor;
	t_rgb		ceiling;
}	t_map;

typedef struct s_frame
{
	void	*frame;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_frame;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# define SUCCESS	1
# define ERROR		0

# define WIDTH		320
# define HEIGHT		200
# define FOV		60

# define SPEED		0.5

# define RED		0xFF0000
# define GREEN		0x00FF00
# define WHITE		0x0000FF

void	parse_map(char *filepath, t_map *map);
int		parse_elements(t_map *map, char *content);

void	load_assets(t_map map);
void	get_values(t_map *map, double angle);

t_frame	create_frame(t_mlx *mlx);
void	draw_frame(t_map *map, int *img_data, int x);

#endif