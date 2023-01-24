/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:36:28 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/25 00:06:47 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dxy	get_inc(double angle, int side)
{
	t_dxy	inc;

	if (side == NORTH)
	{
		inc.y = -SCALE;
		inc.x = inc.y / tan(deg_to_rad(angle));
	}
	else if (side == SOUTH)
	{
		inc.y = SCALE;
		inc.x = inc.y / tan(deg_to_rad(angle));
	}
	else if (side == WEST)
	{
		inc.x = -SCALE;
		inc.y = inc.x * tan(deg_to_rad(angle));
	}
	else
	{
		inc.x = SCALE;
		inc.y = inc.x * tan(deg_to_rad(angle));
	}
	return (inc);
}

int	angle_side(double angle, int side)
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
		a.y = ((int)(pos.y / SCALE)) * SCALE - 0.000001;
	else if (side == SOUTH)
		a.y = ((int)(pos.y / SCALE)) * SCALE + SCALE;
	a.x = (pos.y - a.y) / -tan(deg_to_rad(angle)) + pos.x;
	return (a);
}

t_dxy	first_vpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a;

	if (side == WEST)
		a.x = ((int)(pos.x / SCALE)) * SCALE - 0.00000169;
	else if (side == EAST)
		a.x = ((int)(pos.x / SCALE)) * SCALE + SCALE;
	a.y = (pos.x - a.x) * -tan(deg_to_rad(angle)) + pos.y;
	return (a);
}

t_ray	ray_info(t_dxy point, int side, double dst)
{
	t_ray	ray;

	ray.cord = point;
	ray.side = side;
	ray.wall_height = dst;
	return (ray);
}
