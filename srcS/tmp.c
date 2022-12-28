/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:45:29 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/28 20:41:29 by ommohame         ###   ########.fr       */
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

void	draw_map(t_map map)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (map.map[i][j] == '1')
				draw_box(map, j * 64, i * 64, 63, RED);
		}
	}
	draw_box(map, map.player.pos.x - 1, map.player.pos.y - 1, 2, WHITE);
	// mlx_pixel_put(map.mlx.mlx, map.mlx.tmp, map.player.pos.x, map.player.pos.y, GREEN);
}