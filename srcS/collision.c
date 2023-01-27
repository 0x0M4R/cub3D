/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:24:09 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/27 15:46:41 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	forward_collision(t_data *data)
{
	int		i;
	size_t	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[FORWARD] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x + (cos(deg_to_rad(angle)) * (SCALE / 8));
		point.y = data->player->pos.y + (sin(deg_to_rad(angle)) * (SCALE / 8));
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
	size_t	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[BACKWARD] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x - (cos(deg_to_rad(angle)) * (SCALE / 8));
		point.y = data->player->pos.y - (sin(deg_to_rad(angle)) * (SCALE / 8));
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
	size_t	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[LEFTT] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x - (cos(deg_to_rad(90 + angle)) * (SCALE / 8));
		point.y = data->player->pos.y - (sin(deg_to_rad(90 + angle)) * (SCALE / 8));
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
	size_t	angle;
	t_dxy	point;

	i = -1;
	data->player->collision[RIGHTT] = FALSE;
	angle = fix_angle(data->player->angle - 30);
	while (++i < 7)
	{
		point.x = data->player->pos.x + (cos(deg_to_rad(90 + angle)) * (SCALE / 8));
		point.y = data->player->pos.y + (sin(deg_to_rad(90 + angle)) * (SCALE / 8));
		if (check_walls(data->map, point) == TRUE)
		{
			data->player->collision[RIGHTT] = TRUE;
			break ;
		}
		angle = fix_angle(angle + 10);
	}
}

void	collision_check(t_data *data)
{
	forward_collision(data);
	backward_collision(data);
	left_collision(data);
	right_collision(data);
}
