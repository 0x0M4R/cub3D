/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 23:07:55 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	alpha_pixel_put(int *img_data, int x, int y, int color)
{
	img_data[y * WIDTH + x] = color;
}

t_frame	create_frame(void *mlx, int x, int y)
{
	t_frame	frame;

	frame.frame = mlx_new_image(mlx, x, y);
	frame.data = (int *)mlx_get_data_addr(
			frame.frame, &frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

void	draw_frame(int *img_data, double wall_height, int x)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = (HEIGHT / 2) - (wall_height / 2);
	j = (HEIGHT / 2) + (wall_height / 2);
	while (k < i)
		alpha_pixel_put(img_data, x, k++, RED);
	while (i < j)
		alpha_pixel_put(img_data, x, i++, WHITE);
	k = j;
	while (k < HEIGHT)
		alpha_pixel_put(img_data, x, k++, BLACK);
	return ;
}
