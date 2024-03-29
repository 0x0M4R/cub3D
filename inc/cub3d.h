/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:47:46 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/05 02:52:28 by oabdalla         ###   ########.fr       */
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

enum e_bool {
	TRUE = 1,
	FALSE = 0
};

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
	ON_DESTROY = 17,
	LEFT_CLICK = 1,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5
};

enum e_colors {
	RED = 0xFF0000,
	GREEN = 0x00FF00,
	BLUE = 0x0000FF,
	WHITE = 0xFFFFFF,
	YELLOW = 0xFFFF00,
	BLACK = 0x000000
};

enum e_door {
	NOT = 0,
	OPEN = 1,
	CLOSE = 2,
};

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

enum e_move {
	FORWARD = 0,
	BACKWARD = 1,
	LEFTT = 2,
	RIGHTT = 3
};

# define STEP 20
# define SCALE 128
# define SPEED 16
# define MINIMAP 5
# define MINIMAP_SCALE 32
# define WIN_WIDTH 720
# define WIN_HEIGHT 640
# define FOV 60

# define MAP_CHARS " 01NSEWC"
# define MAP_OBJS "01NSEWC"
# define DOOR_PATH "xpms/door.xpm"
# define GUN_PATH "xpms/gun"

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

/********* ASSETS ***********/
void		invalid_asset(void *mlx_ptr, t_textures *tex, int i, int type);
int			load_walls(void *mlx_ptr, t_textures *tex);
int			load_gun(void *mlx_ptr, t_textures *tex);
int			load_door(void *mlx_ptr, t_textures *tex);

/************ GAME ENGINE **********/
int			keys(int keycode, t_data *data);
int			mouse_move(t_data *data);
int			mouse_keys(int key, int x, int y, t_data *data);

/************ MEM MANG *************/
int			ft_exit(t_data *data);

/************ RENDER *************/
void		alpha_pixel_put(int *img_data, t_ixy point, int color, int width);
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
void		invalid_asset(void *mlx_ptr, t_textures *tex, int i, int type);
char		*check_element_error(size_t elem, size_t *count);

/********** BONUS ***********/
int			minimap(t_data *data);
int			doors(t_data *data);
void		collision(t_data *data, int key);

#endif
