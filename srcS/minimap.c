/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:36:58 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/27 17:53:46 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_box(int *img_data, t_ixy start, int size, int color)
{
	int		i;
	int		j;

	j = -1;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
			alpha_pixel_put(img_data, (t_ixy){start.x + i,
				start.y + j}, color, MINIMAP_SCALE * MINIMAP);
	}
	return (0);
}

static void	pick_square(t_data *data, int *img_data, t_ixy map, t_ixy minimap)
{
	if (data->map->map[(int)map.y][(int)map.x] == '1')
		draw_box(img_data, minimap, MINIMAP_SCALE - 1, BLUE);
	else if (data->map->map[(int)map.y][(int)map.x] == 'C')
		draw_box(img_data, minimap, MINIMAP_SCALE - 1, RED);
	else if (data->map->map[(int)map.y][(int)map.x] == 'O')
		draw_box(img_data, minimap, MINIMAP_SCALE - 1, GREEN);
	else
		draw_box(img_data, minimap, MINIMAP_SCALE - 1, WHITE);
	if ((int)(data->player->pos.x / SCALE) == (int)map.x
		&& (int)(data->player->pos.y / SCALE) == (int)map.y)
		draw_box(img_data, (t_ixy){minimap.x + (MINIMAP_SCALE * 3 / 8),
			minimap.y + (MINIMAP_SCALE * 3 / 8)},
			MINIMAP_SCALE / 4, BLACK);
}

static void	draw_line(int *img_data, double angle, int color)
{
	int		tangent;
	t_dxy	ray;
	t_dxy	player;

	tangent = 0;
	ray = (t_dxy){0, 0};
	player.x = (MINIMAP / 2.0) * MINIMAP_SCALE;
	player.y = (MINIMAP / 2.0) * MINIMAP_SCALE;
	while (tangent < MINIMAP_SCALE / 2)
	{
		alpha_pixel_put(img_data, (t_ixy){player.x + ray.x, player.y + ray.y},
			color, MINIMAP_SCALE * MINIMAP);
		ray.x = cos(deg_to_rad(angle)) * tangent;
		ray.y = sin(deg_to_rad(angle)) * tangent;
		tangent += 1;
	}
}

static void	draw_minimap(t_data *data, int *img_data)
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
	draw_line(img_data, data->player->angle, BLACK);
}

int	minimap(t_data *data)
{
	t_frame	mini_f;

	mini_f = create_frame(data->mlx_ptr,
			MINIMAP * MINIMAP_SCALE, MINIMAP * MINIMAP_SCALE);
	draw_minimap(data, mini_f.data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, mini_f.frame, 0, 0);
	mlx_destroy_image(data->mlx_ptr, mini_f.frame);
	return (TRUE);
}
