/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:11:47 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/16 21:18:10 by ommohame         ###   ########.fr       */
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
# include "debug.h"
// # include "data.h"

enum e_key {
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
	UP			= 1,
	DOWN		= 2,
	LEFT		= 3,
	RIGHT		= 4,
	VERTICAL	= 5,
	HORIZONTAL	= 6
};

# define SCALE 64

# define FLOOR_ID -5
# define CEILING_ID -6


int	parse_elements(t_data *data, char *content);

/*****OMARRRRR*****/
double	get_values(t_data *data, double angle);

t_frame	create_frame(void *mlx, int x, int y);
void	draw_frame(int *img_data, double wall_height, int x);

void	find_player(t_data *data);

int		keys(int keycode, t_data *data);
int		game_loop(t_data *data);

double	deg_to_rad(double deg);
double	get_dst(t_dxy p1, t_dxy p2);
double	fix_angle(double angle);

#endif
