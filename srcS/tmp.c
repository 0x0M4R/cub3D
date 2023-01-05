/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:45:29 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/05 16:49:56 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_frame *data, int x, int y, int color)
{
	if(x<=320 && y <=320 && x >=0 && y>=0)
	{
	data->data[y * 320 + x] = color;
	}
}

int draw_box(t_frame tmp, int x, int y, int size, int colour)
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
			my_mlx_pixel_put(&tmp, x + i, y + j, colour);
			i++;
		}
		j++;
	}
	// mlx_pixel_put(map->mlx.mlx, map->mlx.win, (73*map->player_pos_x), (73*map->player_pos_y), 0xFFFFFF);
	return (0);
}
void draw_ray(t_map map, int ray_x, int ray_y, int angle)
{
	int	tangent;

	tangent = 0;
	while(tangent < 50)
	{
		my_mlx_pixel_put(&tmp, map.player.pos.x + ray_x, map.player.pos.y + ray_y, 0x4b0082);
		ray_x = cos(deg_to_rad(angle)) * tangent;
		ray_y = sin(deg_to_rad(angle)) * tangent;
		tangent += 1;
	}
}
void	draw_map(t_map map)
{
	//mlx_clear_window(map.mlx.mlx, map.mlx.tmp);
	tmp = create_frame(&map.mlx, 320, 320);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (map.map[i][j] == '1')
				draw_box(tmp, j * 64, i * 64, 63, RED);
		}
	}
	// draw_ray(map, 0, 0, map.player.angle);
	// draw_ray(map, 30, 30, map.player.angle + 10);
	// mlx_pixel_put(map.mlx.mlx, map.mlx.tmp, map.player.pos.x, map.player.pos.y, GREEN);
}

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
 
void line(t_map map, int X0, int Y0, int X1, int Y1, int color)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++) {
			if(X<=320 && Y <=320 && X >=0 && Y>=0)
			{
		my_mlx_pixel_put(&tmp, (int)X, (int)Y, color);
		X += Xinc;
		Y += Yinc;
			}
			else
			break;
	}
	draw_box(tmp, map.player.pos.x - 3, map.player.pos.y - 3, 6, WHITE);
	draw_ray(map, 0, 0, map.player.angle);
}