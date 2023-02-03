/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:24:09 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/03 19:06:03 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	forward_collision(t_data *data)
{
	int		i;
	double	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[FORWARD] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x + (cos(deg_to_rad(angle)) * (STEP));
		point.y = data->player->pos.y + (sin(deg_to_rad(angle)) * (STEP));
		if (check_walls(data->map, point) == TRUE)
		{
			data->player->collision[FORWARD] = TRUE;
			break ;
		}
		angle = fix_angle(angle + 10);
	}
}

static void	backward_collision(t_data *data)
{
	int		i;
	double	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[BACKWARD] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x - (cos(deg_to_rad(angle)) * (STEP));
		point.y = data->player->pos.y - (sin(deg_to_rad(angle)) * (STEP));
		if (check_walls(data->map, point) == TRUE)
		{
			data->player->collision[BACKWARD] = TRUE;
			break ;
		}
		angle = fix_angle(angle + 10);
	}
}

static void	left_collision(t_data *data)
{
	int		i;
	double	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[LEFTT] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x
			- (cos(deg_to_rad(90 + angle)) * (STEP));
		point.y = data->player->pos.y
			- (sin(deg_to_rad(90 + angle)) * (STEP));
		if (check_walls(data->map, point) == TRUE)
		{
			data->player->collision[LEFTT] = TRUE;
			break ;
		}
		angle = fix_angle(angle + 10);
	}
}

static void	right_collision(t_data *data)
{
	int		i;
	double	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[RIGHTT] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x
			+ (cos(deg_to_rad(90 + angle)) * (STEP));
		point.y = data->player->pos.y
			+ (sin(deg_to_rad(90 + angle)) * (STEP));
		if (check_walls(data->map, point) == TRUE)
		{
			data->player->collision[RIGHTT] = TRUE;
			break ;
		}
		angle = fix_angle(angle + 10);
	}
}

void	collision(t_data *data, int key)
{
	if (key == W || key == UP || key == SCROLL_UP)
		forward_collision(data);
	else if (key == S || key == DOWN || key == SCROLL_DOWN)
		backward_collision(data);
	else if (key == A)
		left_collision(data);
	else if (key == D)
		right_collision(data);
}
