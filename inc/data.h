/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:13:34 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/26 19:26:06 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/**
 * @brief This structure defines an RGB color
 *
 */
typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

/**
 * @brief This structure holds all the data to define a frame (image)
 *
 * NOTE: data stores the value of mlx_get_address, this variable has been
 * 		typecasted into an integer pointer.
 */
typedef struct s_frame
{
	void	*frame;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		img_width;
	int		img_height;
}	t_frame;

/**
 * @brief This structure holds all the texture paths
 *
 */
typedef struct s_textures
{
	int			ceiling;
	int			floor;
	int			img_width;
	char		*walls_path[4];
	t_frame		*walls[4];
}	t_textures;

/**
 * @brief This structure defines a vector as an integer
 *
 * NOTE: ixy stands for integer x & y
 */
typedef struct s_ixy
{
	int		x;
	int		y;
}	t_ixy;

/**
 * @brief This structure defines a vector as an double
 *
 * NOTE: dxy stands for double x & y
 */
typedef struct s_dxy
{
	double	x;
	double	y;
}	t_dxy;

typedef struct s_player
{
	t_dxy	pos;
	double	angle;
	int		collision[4];
}				t_player;

typedef struct s_map
{
	size_t	width;
	size_t	height;
	char	**map;
}				t_map;

typedef struct s_ray
{
	t_dxy	cord;
	int		side;
	int		door;
	double	wall_height;
}	t_ray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*tmp_win_ptr;
	int			err;
	t_textures	*texts;
	t_player	*player;
	t_map		*map;
}				t_data;
#endif
