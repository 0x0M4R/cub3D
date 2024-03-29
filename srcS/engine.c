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

void	player_movement(int key, t_data *data)
{
	if ((key == W || key == UP) && data->player->collision[FORWARD] == FALSE)
	{
		data->player->pos.x += cos(deg_to_rad(data->player->angle)) * STEP;
		data->player->pos.y += sin(deg_to_rad(data->player->angle)) * STEP;
	}
	else if ((key == S || key == DOWN)
		&& data->player->collision[BACKWARD] == FALSE)
	{
		data->player->pos.x -= cos(deg_to_rad(data->player->angle)) * STEP;
		data->player->pos.y -= sin(deg_to_rad(data->player->angle)) * STEP;
	}
	else if (key == A && data->player->collision[LEFTT] == FALSE)
	{
		data->player->pos.x
			-= cos(deg_to_rad(90 + data->player->angle)) * STEP;
		data->player->pos.y
			-= sin(deg_to_rad(90 + data->player->angle)) * STEP;
	}
	else if (key == D && data->player->collision[RIGHTT] == FALSE)
	{
		data->player->pos.x
			+= cos(deg_to_rad(90 + data->player->angle)) * STEP;
		data->player->pos.y
			+= sin(deg_to_rad(90 + data->player->angle)) * STEP;
	}
}

int	keys(int key, t_data *data)
{
	collision(data, key);
	if (key == W || key == UP || key == S || key == DOWN
		|| key == A || key == D)
		player_movement(key, data);
	else if (key == E)
		doors(data);
	else if (key == LEFT)
		data->player->angle -= SPEED;
	else if (key == RIGHT)
		data->player->angle += SPEED;
	else if (key == ESC || key == Q)
		ft_exit(data);
	else if (key == ENTER)
	{
		if (data->is_mouse == TRUE)
			data->is_mouse = FALSE;
		else
			data->is_mouse = TRUE;
	}
	return (TRUE);
}

int	mouse_move(t_data *data)
{
	int		diff;

	if (data->is_mouse == FALSE)
	{
		mlx_mouse_get_pos(data->win_ptr, &data->mouse.x, &data->mouse.y);
		diff = ((WIN_WIDTH / 2) - data->mouse.x) / 50;
		data->player->angle -= diff;
		mlx_mouse_move(data->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	if (data->texts->gun_f != 0)
		data->texts->gun_f++;
	if (data->texts->gun_f == 5)
		data->texts->gun_f = 0;
	return (TRUE);
}

int	mouse_keys(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	collision(data, key);
	if (key == LEFT_CLICK)
	{
		if (data->texts->gun_f == 0)
			data->texts->gun_f++;
	}
	if (key == SCROLL_UP && data->player->collision[FORWARD] == FALSE)
	{
		data->player->pos.x += cos(deg_to_rad(data->player->angle)) * STEP;
		data->player->pos.y += sin(deg_to_rad(data->player->angle)) * STEP;
	}
	if (key == SCROLL_DOWN && data->player->collision[BACKWARD] == FALSE)
	{
		data->player->pos.x -= cos(deg_to_rad(data->player->angle)) * STEP;
		data->player->pos.y -= sin(deg_to_rad(data->player->angle)) * STEP;
	}
	return (TRUE);
}

int	game_loop(t_data *data)
{
	int		x;
	double	angle;
	double	ang_inc;
	t_ray	ray;
	t_frame	rays_f;

	x = 0;
	mouse_move(data);
	angle = fix_angle(data->player->angle - (FOV / 2));
	ang_inc = (double)FOV / (double)WIN_WIDTH;
	rays_f = create_frame(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	while (x < WIN_WIDTH)
	{
		ray = get_values(data, angle);
		draw_frame(data->texts, rays_f.data, ray, x);
		angle = fix_angle(angle + ang_inc);
		x++;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, rays_f.frame, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texts
		->gun[data->texts->gun_f]->frame, WIN_WIDTH * 0.5, WIN_HEIGHT * 0.40);
	mlx_destroy_image(data->mlx_ptr, rays_f.frame);
	minimap(data);
	return (TRUE);
}
