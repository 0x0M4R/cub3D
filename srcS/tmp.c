/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:45:29 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/31 14:59:49 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_box(t_map map, int x, int y, int size, int colour)
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
			mlx_pixel_put(map.mlx.mlx, map.mlx.tmp, x + i, y + j, colour);
			i++;
		}
		j++;
	}
	// mlx_pixel_put(map->mlx.mlx, map->mlx.win, (73*map->player_pos_x), (73*map->player_pos_y), 0xFFFFFF);
	return (0);
}
void draw_ray(t_map map, int ray_x, int ray_y, int angle)
{
	// int	ray_x;
	// int	ray_y;
	int	tangent;

	tangent = 0;
	// ray_x = 0;
	// ray_y = 0;
	while(map.player.pos.x + ray_x < (64 * 5) && map.player.pos.y + ray_y < (64 * 5))
	{
		mlx_pixel_put(map.mlx.mlx, map.mlx.tmp, map.player.pos.x - ray_x, map.player.pos.y - ray_y, YELLOW);
		ray_x = cos(deg_to_rad(angle)) * tangent;
		ray_y = sin(deg_to_rad(angle)) * tangent;
		tangent += 1;
	}
}
void	draw_map(t_map map)
{
	static int	old_pos_x;
	static int	old_pos_y;

	mlx_clear_window(map.mlx.mlx, map.mlx.tmp);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (map.map[i][j] == '1')
				draw_box(map, j * 64, i * 64, 63, RED);
		}
	}
	if (old_pos_x != 0 && old_pos_y != 0)
		draw_box(map, old_pos_x - 1, old_pos_y - 1, 2, BLACK);
	draw_box(map, map.player.pos.x - 1, map.player.pos.y - 1, 2, WHITE);
	old_pos_x = map.player.pos.x;
	old_pos_y = map.player.pos.y;
	// draw_ray(map, 0, 0, map.player.angle);
	// draw_ray(map, 30, 30, map.player.angle + 10);
	// mlx_pixel_put(map.mlx.mlx, map.mlx.tmp, map.player.pos.x, map.player.pos.y, GREEN);
}

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
 
void line(t_map map, int X0, int Y0, int X1, int Y1)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
 
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;
 
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++) {
		mlx_pixel_put(map.mlx.mlx, map.mlx.tmp, (int)X, (int)Y, GREEN);
		X += Xinc;
		Y += Yinc;
	}
}