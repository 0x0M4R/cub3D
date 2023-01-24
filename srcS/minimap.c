/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:36:58 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 23:28:16 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_box(int *img_data, t_dxy point, size_t size, int color)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			alpha_pixel_put(img_data, point.x + i, point.y + j, color);
	}
}

void	draw_minimap(t_data *data, int *img_data)
{
	ssize_t	i;
	ssize_t	j;
	t_dxy	point;

	point = (t_dxy){0, 0};
	i = (int)(data->player->pos.y / SCALE) - 2;
	while (i < (ssize_t)data->map->height && i < MINIMAP)
	{
		j = (int)(data->player->pos.x / SCALE) - 2;
		while (j < (ssize_t)data->map->width && j < MINIMAP)
		{
			point.x = j * SCALE;
			point.y = i * SCALE;
			if (i < 0 || i > (ssize_t)data->map->height
				|| j > (ssize_t)data->map->width || j < 0)
				;
			else if (data->map->map[i][j] == '1')
				draw_box(img_data, point, SCALE, RED);
			else if (data->map->map[i][j] == '0')
				draw_box(img_data, point, SCALE, WHITE);
			else if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S' \
				|| data->map->map[i][j] == 'E' || data->map->map[i][j] == 'W')
				draw_box(img_data, point, SCALE, GREEN);
			else
				draw_box(img_data, point, SCALE, BLUE);
			j++;
		}
		i++;
	}
}
