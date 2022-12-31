/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:22:41 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/31 17:09:32 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_map *map)
{
    printf("angle: %f",map->player.angle);
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
	frame = create_frame(&map->mlx);
	// draw_map(*map);
	while (x < WIDTH)
	{
		wall_height = get_values(map, angle);
		draw_frame(frame.data, wall_height, x);
		angle = fix_angle(angle + ang_inc);
		x++;
	}
	mlx_clear_window(map->mlx.mlx, map->mlx.win);
	mlx_put_image_to_window(map->mlx.mlx, map->mlx.win, frame.frame, 0, 0);
	mlx_destroy_image(map->mlx.mlx, frame.frame);
	return (SUCCESS);
}