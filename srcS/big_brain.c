/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 22:28:55 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********** WIP *************/

int		angle_side(double angle, int side)
{
	if (side == HORIZONTAL)
	{
		if (angle >= 0.0 && angle < 180.0)
			return (SOUTH);
		else
			return (NORTH);
	}
	else
	{
		if (angle >= 90.0 && angle < 270.0)
		 	return (WEST);
		else
			return (EAST);
	}
}

t_dxy	first_hpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a;

	if (side == NORTH)
		a.y = (int)(pos.y / SCALE) * SCALE - 0.000001;
	else if (side == SOUTH)
		a.y = (int)(pos.y / SCALE) * SCALE + SCALE;
	a.x = (pos.y - a.y) / -tan(deg_to_rad(angle)) + pos.x;
	return (a);
}

t_dxy	first_vpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a;

	if (side == WEST)
		a.x = (int)(pos.x / SCALE) * SCALE - 0.000001;
	else if (side == EAST)
		a.x = (int)(pos.x / SCALE) * SCALE + SCALE;
	a.y = (pos.x - a.x) * -tan(deg_to_rad(angle)) + pos.y;
	return (a);
}

t_dxy	get_inc(double angle, int side, int dir)
{
	t_dxy	inc;

	if (side == HORIZONTAL)
	{
		if (dir == NORTH)
			inc.y = -SCALE;
		else
			inc.y = SCALE;
		inc.x = inc.y / tan(deg_to_rad(angle));
	}
	else
	{
		if (dir == WEST)
			inc.x = -SCALE;
		else
			inc.x = SCALE;
		inc.y = inc.x * tan(deg_to_rad(angle));
	}
	return (inc);
}

void	get_corners_inc(t_dxy *inc1, t_dxy *inc2)
{
	inc1[0] = (t_dxy){-1, 0};
	inc2[0] = (t_dxy){0, 1};
	inc1[1] = (t_dxy){-1, 0};
	inc2[1] = (t_dxy){0, -1};
	inc1[2] = (t_dxy){1, 0};
	inc2[2] = (t_dxy){0, -1};
	inc1[3] = (t_dxy){1, 0};
	inc2[3] = (t_dxy){0, 1};
}

int check_walls(t_map *map, t_dxy a) 
{
	int		i;
	t_dxy	inc1[4];
	t_dxy	inc2[4];
	t_dxy	corner1;
	t_dxy	corner2;

	i = -1;
	if ((int)(a.x / SCALE) < 0 || (int)(a.x / SCALE) > (int)map->width - 1
	|| (int)(a.y / SCALE) < 0 || (int)(a.y / SCALE) > (int)map->height - 1)
		return (SUCCESS);
	if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == 1)
		return (SUCCESS);
	get_corners_inc(inc1, inc2);
	while (++i < 4)
	{
		corner1 = (t_dxy){a.x + inc1[i].x, a.y + inc1[i].y};
		corner2 = (t_dxy){a.x + inc2[i].x, a.y + inc2[i].y};
		if (corner1.x < 0 || corner1.x > (int)map->width * SCALE
			|| corner1.y < 0 || corner1.y > (int)map->height * SCALE
			|| corner2.x < 0 || corner2.x > (int)map->width * SCALE
			|| corner2.y < 0 || corner2.y > (int)map->height * SCALE)
			 ;
		else if (map->map[(int)(corner1.y / SCALE)][(int)(corner1.x / SCALE)] == '1'
		&& map->map[(int)(corner2.y / SCALE)][(int)(corner2.x / SCALE)] == '1')
			return (SUCCESS);
	}
	return (ERROR);
}

double	dda(t_data *data, double angle, t_dxy a, int side, int dir)
{
	t_dxy	inc;

	inc = get_inc(angle, side, dir);
	while (1)
	{
		if (check_walls(data->map, a) == SUCCESS)
		{
			if (DEBUG)
			{
				if (side == VERTICAL)
					line(*data, data->player->pos.x, data->player->pos.y, a.x, a.y, BLUE);
				if (side == HORIZONTAL)
			 		line(*data, data->player->pos.x, data->player->pos.y, a.x, a.y, GREEN);
			}
			break ;
		}
		a.x += inc.x;
		a.y += inc.y;
	}
	return (get_dst(data->player->pos, a));
}

double	rays(t_data *data, double angle)
{
	int		side;
	t_dxy	hpoint;
	t_dxy	vpoint;
	double	hray_dst;
	double	vray_dst;

	hray_dst = 1e30;
	vray_dst = 1e30;
	if (angle != 180.0 && angle != 0.0)
	{
		side = angle_side(angle, HORIZONTAL);
		hpoint = first_hpoint(data->player->pos, angle, side);
		hray_dst = dda(data, angle, hpoint, HORIZONTAL, side);
	}
	if (angle != 90.0 && angle != 270.0)
	{
		side = angle_side(angle, VERTICAL);
		vpoint = first_vpoint(data->player->pos, angle, side);
		vray_dst = dda(data, angle, vpoint, VERTICAL, side);
	}
	if (hray_dst < vray_dst)
		return (hray_dst);
	else
		return (vray_dst);
}

double	fishazz(double ray_dst, double angle, double p_angle)
{
	double	angleito;

	angleito = deg_to_rad(p_angle - angle);
	if (angleito < 0)
		angleito += 2 * M_PI;
	else if (angleito > 2 * M_PI)
		angleito -= 2 * M_PI;
	return (ray_dst * cos((angleito)));
}

double get_values(t_data *data, double angle)
{
	double	ray_dst;

	ray_dst = rays(data, angle);
	ray_dst = fishazz(ray_dst, angle, data->player->angle);
	ray_dst = (SCALE * HEIGHT / 2) / ray_dst;
	if (ray_dst > HEIGHT)
		ray_dst = HEIGHT;
	return (ray_dst);
}
