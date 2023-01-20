/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 23:37:32 by ommohame         ###   ########.fr       */
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

double	check_grids(t_data *data, double angle, t_dxy *a, int side)
{
	t_dxy	inc;

	inc = get_inc(angle, side);
	while (1)
	{
		if (check_walls(data->map, *a) == SUCCESS)
		{
			if (DEBUG)
			{
				if (side == EAST || side == WEST)
					line(*data, data->player->pos.x,
						data->player->pos.y, a->x, a->y, BLUE);
				else if (side == NORTH || side == SOUTH)
					line(*data, data->player->pos.x,
						data->player->pos.y, a->x, a->y, GREEN);
			}
			break ;
		}
		a->x += inc.x;
		a->y += inc.y;
	}
	return (get_dst(data->player->pos, *a));
}

t_render	render_vales(t_dxy point, double angle, int side, double dst)
{
	t_render	render;

	render.ray_loc = point;
	render.side = side;
	render.wall_height = dst;
}

t_render	rays(t_data *data, double angle, t_render *render)
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
		return (render_vales(hpoint, angle, get_side(angle, HORIZONTAL), hray_dst));
	else
		return (render_vales(vpoint, angle, get_side(angle, VERTICAL), vray_dst));
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

t_render	get_values(t_data *data, double angle)
{
	double		ray_dst;

	ray_dst = rays(data, angle. &render);
	ray_dst = fishazz(ray_dst, angle, data->player->angle);
	ray_dst = (SCALE * HEIGHT / 2) / ray_dst;
	if (ray_dst > HEIGHT)
		ray_dst = HEIGHT;
	return (ray_dst);
}
