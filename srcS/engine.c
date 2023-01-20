/* ************************************************************************** */
/*		                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:22:41 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 00:36:35 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_data *data)
{
	if (key == 13)
	{
		data->player->pos.x += cos(deg_to_rad(data->player->angle)) * SPEED;
		data->player->pos.y += sin(deg_to_rad(data->player->angle)) * SPEED;
	}
	else if (key == 1)
	{
		data->player->pos.x -= cos(deg_to_rad(data->player->angle)) * SPEED;
		data->player->pos.y -= sin(deg_to_rad(data->player->angle)) * SPEED;
	}
	else if (key == 0)
		data->player->angle -= SPEED;
	else if (key == 2)
		data->player->angle += SPEED;
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
		draw_frame(frame.data, ray, x);
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
