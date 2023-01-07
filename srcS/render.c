/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/06 13:25:22 by oabdalla         ###   ########.fr       */
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
	frame.data = (int *)mlx_get_data_addr(
		frame.frame, &frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

void	draw_frame(t_map *map, int *img_data, double wall_height, int x)
{
	int		i;
	int		j;
	int		k;

	static double texx;

	if ((int)texx > map->n_texture.img_height)
		texx = 0;
	k = 0;
	i = (HEIGHT / 2) - (wall_height / 2);
 	j = (HEIGHT / 2) + (wall_height / 2);
	double step = (map->n_texture.img_height/wall_height);

	double texp = (i - HEIGHT/2 + wall_height/2)*step;
	while (k < i) // Ceilling color
		alpha_pixel_put(img_data, x, k++, RED);
	while (i < j) // Floor color
	{
		int texy = (int)texp & (map->n_texture.img_height - 1);
		texp += step;
		alpha_pixel_put(img_data, x, i++, map->n_texture.image.data[texy * map->n_texture.img_height + (int)texx]);
		// mlx_pixel_put(map->mlx.mlx, map->mlx.win, x, i++, RED);
	}
	texx = texx + step;
	k = j;
	while (k < HEIGHT)
		alpha_pixel_put(img_data, x, k++, BLACK);
	return ;
}