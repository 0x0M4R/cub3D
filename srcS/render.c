/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/29 15:20:59 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alpha_pixel_put(int *img_data, t_ixy point, int color, int width)
{
	img_data[point.y * width + point.x] = color;
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
	int			i;
	int			texx;
	int			color;
	double		step;
	t_frame		*image;

	i = ray.side;
	if (ray.door == TRUE)
		image = text->door;
	else
		image = text->walls[i - 1];
	if (ray.side == NORTH || ray.side == SOUTH)
		texx = (int)ray.cord.x % image->img_height;
	else
		texx = (int)ray.cord.y % image->img_height;
	step = (image->img_height / ray.wall_height);
	color = image
		->data[(int)*texy * image->img_height + texx];
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
	i = (WIN_HEIGHT / 2) - (ray.wall_height / 2);
	j = (WIN_HEIGHT / 2) + (ray.wall_height / 2);
	while (k < i)
		alpha_pixel_put(img_data, (t_ixy){x, k++}, text->ceiling, WIN_WIDTH);
	while (i < j)
	{
		color = get_texture_color(text, ray, &texy);
		alpha_pixel_put(img_data, (t_ixy){x, i++}, color, WIN_WIDTH);
	}
	k = j;
	while (k < WIN_HEIGHT)
		alpha_pixel_put(img_data, (t_ixy){x, k++}, text->floor, WIN_WIDTH);
}
