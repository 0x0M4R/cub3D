/* ************************************************************************** */
/*		                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:22:41 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/12 15:45:20 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_data *data)
{
	if (key == W || key == UP)
	{
		data->player->pos.x += cos(deg_to_rad(data->player->angle)) * SPEED;
		data->player->pos.y += sin(deg_to_rad(data->player->angle)) * SPEED;
	}
	else if (key == S || key == DOWN)
	{
		data->player->pos.x -= cos(deg_to_rad(data->player->angle)) * SPEED;
		data->player->pos.y -= sin(deg_to_rad(data->player->angle)) * SPEED;
	}
	else if (key == A || key == LEFT)
		data->player->angle -= SPEED;
	else if (key == D || key == RIGHT)
		data->player->angle += SPEED;
	else if (key == ESC || key == Q)
		ft_exit(data);
	return (SUCCESS);
}

int	game_loop(t_data *data)
{
	int		x;
	double	angle;
	double	ang_inc;
	t_ray	ray;
	t_frame	frame;

	x = 0;
	angle = fix_angle(data->player->angle - (FOV / 2));
	ang_inc = (double)FOV / (double)WIDTH;
	frame = create_frame(data->mlx_ptr, WIDTH, HEIGHT);
	if (DEBUG)
		draw_map(*data);
	while (x < WIDTH)
	{
		ray = get_values(data, angle);
		draw_frame(data->texts, frame.data, ray, x);
		angle = fix_angle(angle + ang_inc);
		x++;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, frame.frame, 0, 0);
	if (DEBUG)
		mlx_put_image_to_window(data->mlx_ptr,data->tmp_win_ptr, tmp.frame, 0, 0);
	mlx_destroy_image(data->mlx_ptr, frame.frame);
	return (SUCCESS);
}
