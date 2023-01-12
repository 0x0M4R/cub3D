/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/12 16:19:36 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void	alpha_pixel_put(int *img_data, int x, int y, int color)
{
	img_data[y * WIDTH + x] = color;
}

t_frame	create_frame(t_mlx *mlx, int x, int y)
{
	t_frame	frame;

	frame.frame = mlx_new_image(mlx->mlx, x, y);
	frame.data = (int *)mlx_get_data_addr(\
		frame.frame, &frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

int		get_texture_color(t_map *map, double wall_height, double *texy)
{
	int				texx;
	double			step;
	int				color;
	int				i;

	i = angle_side(map->ray.angle, map->ray.side);
	if (map->ray.side == HORIZONTAL)
		texx = (int)map->ray.ray.x % map->tex[i - 1].img_height;
	else
		texx = (int)map->ray.ray.y % map->tex[i - 1].img_height;
	step = (map->tex[i - 1].img_height / wall_height);
	color = map->tex[i - 1].img.data[(int)*texy * map->tex[i - 1].img_height + texx];
	*texy += step;
	return (color);
}

void	draw_frame(t_map *map, int *img_data, double wall_height, int x)
{
	int		i;
	int		j;
	int		k;
	int		color;
	double	texy;

	texy = 0;
	k = 0;
	i = (HEIGHT / 2) - (wall_height / 2);
	j = (HEIGHT / 2) + (wall_height / 2);
	while (k < i)
		alpha_pixel_put(img_data, x, k++, RED);
	while (i < j)
	{
		color = get_texture_color(map, wall_height, &texy);
		alpha_pixel_put(img_data, x, i++, color);
	}
	k = j;
	while (k < HEIGHT)
		alpha_pixel_put(img_data, x, k++, BLACK);
	return ;
}