/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/27 17:54:21 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	check_grids(t_data *data, double angle, t_dxy *a, int side)
{
	t_dxy	inc;

	inc = get_inc(angle, side);
	while (1)
	{
		if (check_walls(data->map, *a) == TRUE)
			break ;
		a->x += inc.x;
		a->y += inc.y;
	}
	return (get_dst(data->player->pos, *a));
}

t_ray	rays(t_data *data, double angle)
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
		hray_dst = check_grids(data, angle, &hpoint, side);
	}
	if (angle != 90.0 && angle != 270.0)
	{
		side = angle_side(angle, VERTICAL);
		vpoint = first_vpoint(data->player->pos, angle, side);
		vray_dst = check_grids(data, angle, &vpoint, side);
	}
	if (hray_dst < vray_dst)
		return (ray_info(hpoint, angle_side(angle, HORIZONTAL), hray_dst));
	else
		return (ray_info(vpoint, angle_side(angle, VERTICAL), vray_dst));
}

double	fishazz(double ray_dst, double angle, double p_angle)
{
	double	angleito;

	angleito = fix_angle(angle - p_angle);
	angleito = deg_to_rad(angleito);
	return (ray_dst * cos((angleito)));
}

t_ray	get_values(t_data *data, double angle)
{
	t_ray	ray;

	ray = rays(data, angle);
	ray.wall_height = fishazz(ray.wall_height, angle, data->player->angle);
	ray.wall_height = (SCALE * WIN_HEIGHT) / ray.wall_height;
	if (check_map_range(data->map, ray.cord)
		&& data->map->map[(int)(ray.cord.y / SCALE)]
			[(int)(ray.cord.x / SCALE)] == 'C')
			ray.door = TRUE;
	if (ray.wall_height > WIN_HEIGHT)
		ray.wall_height = WIN_HEIGHT;
	collision(data);
	return (ray);
}
