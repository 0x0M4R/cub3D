/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:47:46 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/06 13:10:56 by oabdalla         ###   ########.fr       */
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

#ifndef DEBUG
# define DEBUG 0
#endif

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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_frame
{
	void	*frame;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_frame;

typedef struct s_debug
{
	void	*win;
	t_dxy	ray;
	t_frame	frame;
}	t_debug;

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

typedef struct s_render
{
	int		height;
}	t_render;

typedef struct s_player
{
	double		angle;
	t_dxy		pos;
	t_render	render;
}	t_player;

typedef struct s_texture
{
	char		*path;
	t_frame		image;
	int			img_width;
	int			img_height;
}	t_texture;

typedef struct s_map
{
	char		**map;
	t_mlx		mlx;
	t_player	player;
	double		time;
	double		old_time;
	int			player_direction;
	t_texture		n_texture;
	t_texture		e_texture;
	t_texture		s_texture;
	t_texture		w_texture;
	t_rgb		floor;
	t_rgb		ceiling;
	t_data		debug;		//temporary
}	t_map;

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

# define WIDTH		1280
# define HEIGHT		720
# define FOV		60

# define SPEED		5

# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE		0x0000FF
# define WHITE		0xFFFFFF
# define YELLOW		0xFFFF00
# define BLACK		0x000000

# define SCALE 64
# define UP	1
# define DOWN 2
# define LEFT 3
# define RIGHT 4
# define VERTICAL 5
# define HORIZONTAL 6

t_frame tmp;

void	parse_map(char *filepath, t_map *map);
int		parse_elements(t_map *map, char *content);

void	load_assets(t_map *map);
double	get_values(t_map *map, double angle);

t_frame	create_frame(t_mlx *mlx, int x, int y);
void	draw_frame(t_map *map, int *img_data, double wall_height, int x);

void	find_player(t_map *map);

int		keys(int keycode, t_map *map);
int		game_loop(t_map *map);

double	deg_to_rad(double deg);
double	get_dst(t_dxy p1, t_dxy p2);
double	fix_angle(double angle);

// test
void	draw_map(t_map map);
void	 line(t_map map, int X0, int Y0, int X1, int Y1, int color);

#endif