/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/12 15:53:05 by oabdalla         ###   ########.fr       */
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

void	draw_frame(t_map *map, int *img_data, double wall_height, int x)
{
	int		i;
	int		j;
	int		k;
	int		texx;
	double	step;
	double	texy;

	texy = 0;
	k = 0;
	i = (HEIGHT / 2) - (wall_height / 2);
	j = (HEIGHT / 2) + (wall_height / 2);
	step = (map->tex[0].img_height / wall_height);
	if (map->ray.side == HORIZONTAL)
		texx = (int)map->ray.ray.x % map->tex[0].img_height;
	else
		texx = (int)map->ray.ray.y % map->tex[0].img_height;
	while (k < i)
		alpha_pixel_put(img_data, x, k++, RED);
	while (i < j)
	{
		alpha_pixel_put(img_data, x, i++, map->tex[0].img.data[(int)texy * map->tex[0].img_height + texx]);
		texy += step;
	}
	k = j;
	while (k < HEIGHT)
		alpha_pixel_put(img_data, x, k++, BLACK);
	return ;
}