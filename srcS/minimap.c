/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:36:58 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/25 18:14:34 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_box(int *img_data, t_ixy start, int size, int color)
{
	int		i;
	int		j;

	j = -1;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
			alpha_pixel_put(img_data, start.x + i,
				start.y + j, color, MINIMAP_SCALE * MINIMAP);
	}
	return (0);
}

void	pick_square(t_data *data, int *img_data, t_ixy map, t_ixy minimap)
{
	if (data->map->map[(int)map.y][(int)map.x] == '1')
		draw_box(img_data, minimap, MINIMAP_SCALE - 1, RED);
	else
		draw_box(img_data, minimap, MINIMAP_SCALE - 1, WHITE);
	if ((int)(data->player->pos.x / SCALE) == (int)map.x
		&& (int)(data->player->pos.y / SCALE) == (int)map.y)
		draw_box(img_data, (t_ixy){minimap.x + (MINIMAP_SCALE * 3 / 8),
			minimap.y + (MINIMAP_SCALE * 3 / 8)},
			MINIMAP_SCALE / 4, BLUE);
}

void	draw_minimap(t_data *data, int *img_data)
{
	t_ixy	map;
	t_ixy	minimap;

	minimap = (t_ixy){0, 0};
	map.y = (int)(data->player->pos.y / SCALE) - (int)(MINIMAP / 2);
	while (minimap.y < MINIMAP_SCALE * MINIMAP)
	{
		minimap.x = 0;
		map.x = (int)(data->player->pos.x / SCALE) - (int)(MINIMAP / 2);
		while (minimap.x < MINIMAP_SCALE * MINIMAP)
		{
			if (map.x > (int)data->map->width - 1 || map.x < 0
				|| map.y > (int)data->map->height - 1 || map.y < 0)
				;
			else
				pick_square(data, img_data, map, minimap);
			minimap.x += MINIMAP_SCALE;
			map.x++;
		}
		minimap.y += MINIMAP_SCALE;
		map.y++;
	}
}
