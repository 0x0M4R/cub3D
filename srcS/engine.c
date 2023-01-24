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

// int	collision_check(t_data *data, int key)
// {
// 	int		i;
// 	double	angle;
// 	t_dxy	coll_point;

// 	i = -1;
// 	angle = fix_angle(data->player->angle - (FOV / 2));
// 	coll_point = data->player->pos;
// 	if (key == W || key == UP)
// 	{
// 		while (++i < 3)
// 		{
// 			coll_point.x += cos(deg_to_rad(angle)) * SPEED;
// 			coll_point.y += sin(deg_to_rad(angle)) * SPEED;
// 			if (data->map->map[(int)(coll_point.y / SCALE)][(int)(coll_point.x / SCALE)] == '1')
// 				return (FALSE);
// 			angle = fix_angle(angle + (FOV / 2));
// 		}
// 	}
// 	return (TRUE);
// }

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
	return (TRUE);
}

int	game_loop(t_data *data)
{
	int		x;
	double	angle;
	double	ang_inc;
	t_ray	ray;
	t_frame	mini_f;
	t_frame	rays_f;

	x = 0;
	angle = fix_angle(data->player->angle - (FOV / 2));
	ang_inc = (double)FOV / (double)WIDTH;
	mini_f = create_frame(data->mlx_ptr, MINIMAP * SCALE, MINIMAP * SCALE);
	rays_f = create_frame(data->mlx_ptr, WIDTH, HEIGHT);
	while (x < WIDTH)
	{
		ray = get_values(data, angle);
		draw_frame(data->texts, rays_f.data, ray, x);
		angle = fix_angle(angle + ang_inc);
		x++;
	}
	// draw_minimap(data, mini_f.data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, rays_f.frame, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, mini_f.frame, 0, 0);
	mlx_destroy_image(data->mlx_ptr, rays_f.frame);
	mlx_destroy_image(data->mlx_ptr, mini_f.frame);
	return (TRUE);
}
