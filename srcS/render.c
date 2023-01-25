/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/25 14:53:02 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alpha_pixel_put(int *img_data, int x, int y, int color, int width)
{
	img_data[y * width + x] = color;
}

t_frame	create_frame(void *mlx_ptr, int x, int y)
{
	t_frame	frame;

	frame.frame = mlx_new_image(mlx_ptr, x, y);
	frame.data = (int *)mlx_get_data_addr(\
		frame.frame, &frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

int	get_texture_color(t_textures *text, t_ray ray, double *texy)
{
	int		i;
	int		texx;
	int		color;
	double	step;

	i = ray.side;
	if (ray.side == NORTH || ray.side == SOUTH)
		texx = (int)ray.cord.x % text->walls[i - 1]->img_height;
	else
		texx = (int)ray.cord.y % text->walls[i - 1]->img_height;
	step = (text->walls[i - 1]->img_height / ray.wall_height);
	color = text->walls[i - 1]
		->data[(int)*texy * text->walls[i - 1]->img_height + texx];
	*texy += step;
	return (color);
}

void	draw_frame(t_textures *text, int *img_data, t_ray ray, int x)
{
	int		i;
	int		j;
	int		k;
	int		color;
	double	texy;

	texy = 0;
	k = 0;
	i = (HEIGHT / 2) - (ray.wall_height / 2);
	j = (HEIGHT / 2) + (ray.wall_height / 2);
	while (k < i)
		alpha_pixel_put(img_data, x, k++, text->ceiling, WIDTH);
	while (i < j)
	{
		color = get_texture_color(text, ray, &texy);
		alpha_pixel_put(img_data, x, i++, color, WIDTH);
	}
	k = j;
	while (k < HEIGHT)
		alpha_pixel_put(img_data, x, k++, text->floor, WIDTH);
}
