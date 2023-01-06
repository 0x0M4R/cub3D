/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:22:41 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/06 13:11:29 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_map *map)
{
	if (key == 13) // forward
	{
		map->player.pos.x += cos(deg_to_rad(map->player.angle)) * SPEED;
		map->player.pos.y += sin(deg_to_rad(map->player.angle)) * SPEED;
	}
	else if (key == 1) //backward
	{
		map->player.pos.x -= cos(deg_to_rad(map->player.angle)) * SPEED;
		map->player.pos.y -= sin(deg_to_rad(map->player.angle)) * SPEED;
		// map->player.pos.y -= sin(map->player.angle) * SPEED;
	}
	else if (key == 0) //left
	{
		map->player.angle -= SPEED;
	}
	else if (key == 2) //right
	{
		map->player.angle += SPEED;
	}
	return (SUCCESS);
}

int	game_loop(t_map *map)
{
	int		x; // column number
	double	angle; // angle of the first ray
	double	ang_inc; // the angle difference between each rays
	double	wall_height;
	t_frame	frame;

	x = 0;
	angle = fix_angle(map->player.angle - (FOV / 2));
	ang_inc = (double)FOV / (double)WIDTH;
	// printf("starting angle: %f - ang_inc: %f\n", angle, ang_inc);
	frame = create_frame(&map->mlx, WIDTH, HEIGHT);
	if (DEBUG)
    {
        // map->debug.img = mlx_new_image(map->mlx.mlx, 320, 320);
        // map->debug.addr = mlx_get_data_addr(map->debug.img, &map->debug.bits_per_pixel, &map->debug.line_length,
		// 						&map->debug.endian);
		draw_map(*map);
        // mlx_put_image_to_window(map->mlx.mlx, map->mlx.tmp, map->debug.img, 0, 0);
    }
	while (x < WIDTH)
	{
		wall_height = get_values(map, angle);
		draw_frame(map, frame.data, wall_height, x);
		angle = fix_angle(angle + ang_inc);
		x++;
	}
	mlx_clear_window(map->mlx.mlx, map->mlx.win);
	mlx_put_image_to_window(map->mlx.mlx, map->mlx.win, frame.frame, 0, 0);
    if (DEBUG)
        mlx_put_image_to_window(map->mlx.mlx, map->mlx.tmp, tmp.frame, 0, 0);
	mlx_destroy_image(map->mlx.mlx, frame.frame);
	return (SUCCESS);
}