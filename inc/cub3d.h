/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:47:46 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 17:23:23 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "error_msgs.h"
# include "data.h"

enum e_key {
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	Q = 12,
	E = 14,
	ESC = 53,
	LEFT = 123,
	UP = 126,
	RIGHT = 124,
	DOWN = 125,
	ENTER = 36,
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

enum e_dir {
	NORTH		= 1,
	SOUTH		= 2,
	WEST		= 3,
	EAST		= 4,
	FLOOR		= 5,
	CEILING		= 6,
	VERTICAL	= 7,
	HORIZONTAL	= 8,
};

# define SCALE 64

# define MAP_CHARS " 01NSEW"
# define MAP_OBJS "01NSEW"

/******** PARSER **********/
char		**get_file(char *map_path);
t_textures	*parse_elements(char **file, size_t *line);
t_textures	*get_textures(char **file, size_t *line);
int			parse_map(t_map *map);
size_t		get_width(char **map);
int			check_invalid_char(char **file);
char		**trim_map(char **file);
int			check_surrounding(t_map *map, size_t i, size_t j);
char		**squareazz(char **tmp_map, size_t width, size_t height);
t_ray		get_values(t_data *data, double angle);
int			load_assets(void *mlx_ptr, t_textures *tex);
t_player	*get_player(char **map);
t_data		*parser(char *map_path);

/************ GAME ENGINE **********/
int			keys(int keycode, t_data *data);

/************ MEM MANG *************/
void		ft_exit(t_data *data);

/************ RENDER *************/
t_frame		create_frame(void *mlx, int x, int y);
void		draw_frame(t_textures *text, int *img_data, t_ray ray, int x);

int			game_loop(t_data *data);

/************* RAYCASTING *************/
t_dxy		get_inc(double angle, int side);
t_dxy		first_hpoint(t_dxy pos, double angle, int side);
t_dxy		first_vpoint(t_dxy pos, double angle, int side);
int			check_walls(t_map *map, t_dxy a);
void		get_corners_inc(t_dxy *inc1, t_dxy *inc2);
int			angle_side(double angle, int side);
t_ray		ray_info(t_dxy point, int side, double dst);

/********* UTILS **********/
double		deg_to_rad(double deg);
double		get_dst(t_dxy p1, t_dxy p2);
double		fix_angle(double angle);
void		free_2d(char **str);
size_t		ft_strlenx2(char **str);
int			check_map_range(t_map *map, t_dxy point);

#endif
