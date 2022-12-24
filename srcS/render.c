/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:18:48 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/24 19:22:14 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void	alpha_pixel_put(int *img_data, int x, int y, int color)
{
	img_data[y * WIDTH + x] = color;
}

t_frame	create_frame(t_mlx *mlx)
{
	t_frame	frame;

	frame.frame = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	frame.data = (int *)mlx_get_data_addr(
		frame.frame, &frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

void	draw_frame(t_map *map, int *img_data, int x)
{
	int		i;
	int		j;
	int		height;

	height = map->player.render.height;
	i = (HEIGHT / 2) - (height / 2) - 1;
 	j = (HEIGHT / 2) + (height / 2);
	while (i < j)
		alpha_pixel_put(img_data, x, i++, RED);
		// mlx_pixel_put(map->mlx.mlx, map->mlx.win, x, i++, RED);
	(void)img_data;
	return ;
}