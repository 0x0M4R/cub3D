/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:45:29 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 01:34:13 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_frame *data, int x, int y, int color, int width, int height)
{
	if(x < width && y < height && x >= 0 && y >= 0)
	{
		data->data[y * width + x] = color;
	}
}

int draw_box(t_frame tmp, int x, int y, int size, int colour, int width, int height)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			my_mlx_pixel_put(&tmp, x + i, y + j, colour, width * 64, height * 64);
			i++;
		}
		j++;
	}
	// mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win, (73*data->player_pos_x), (73*data->player_pos_y), 0xFFFFFF);
	return (0);
}
void draw_ray(t_data data, int ray_x, int ray_y, int angle)
{
	int	tangent;

	tangent = 0;
	while(tangent < 50)
	{
		my_mlx_pixel_put(&tmp, data.player->pos.x + ray_x, data.player->pos.y + ray_y, 0x4b0082, data.map->width * 64, data.map->height * 64);
		ray_x = cos(deg_to_rad(angle)) * tangent;
		ray_y = sin(deg_to_rad(angle)) * tangent;
		tangent += 1;
	}
}
void	draw_map(t_data data)
{
	//mlx_clear_window(data.mlx_ptr.mlx_ptr, data.mlx_ptr.tmp);
	tmp = create_frame(&data.mlx_ptr, (data.map->width * 64), (data.map->height * 64));
	for (int i = 0; i < (int)data.map->height; i++)
	{
		for (int j = 0; j < (int)data.map->width; j++)
		{
			if (data.map->map[i][j] == 1)
				draw_box(tmp, j * 64, i * 64, 63, RED, data.map->width, data.map->height);
		}
	}
	// draw_ray(data, 0, 0, data.player->angle);
	// draw_ray(data, 30, 30, data.player->angle + 10);
	// mlx_pixel_put(data.mlx_ptr.mlx_ptr, data.mlx_ptr.tmp, data.player->pos.x, data.player->pos.y, GREEN);
}

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

void line(t_data data, int X0, int Y0, int X1, int Y1, int color)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++) {
			if(X<=(data.map->width * 64) && Y <=(data.map->height * 64) && X >=0 && Y>=0)
			{
		my_mlx_pixel_put(&tmp, (int)X, (int)Y, color, data.map->width * 64, data.map->height * 64);
		X += Xinc;
		Y += Yinc;
			}
			else
			break;
	}
	draw_box(tmp, data.player->pos.x - 3, data.player->pos.y - 3, 6, WHITE, data.map->width, data.map->height);
	draw_ray(data, 0, 0, data.player->angle);
}
