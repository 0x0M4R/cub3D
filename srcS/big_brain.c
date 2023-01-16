/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/12 23:35:37 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********** WIP *************/

// get the angle quadrant for x-axis or y-axis
int		angle_side(double angle, int side)
{
	if (side == HORIZONTAL)
	{
		if (angle >= 0.0 && angle < 180.0)
			return (DOWN);
		else
			return (UP);
	}
	else // vertical
	{
		if (angle >= 90.0 && angle < 270.0)
		 	return (LEFT);
		else
			return (RIGHT);
	}
}

t_dxy	first_hpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a; // first horizontal grid point according to the 2d map

	if (side == UP)
		a.y = (int)(pos.y / SCALE) * SCALE - 1;
	else if (side == DOWN)
		a.y = (int)(pos.y / SCALE) * SCALE + SCALE;
	a.x = (pos.y - a.y) / -tan(deg_to_rad(angle)) + pos.x;
	return (a);
}

t_dxy	first_vpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a; // first vertical grid point according to the 2d map

	if (side == LEFT)
		a.x = (int)(pos.x / SCALE) * SCALE - 1;
	else if (side == RIGHT)
		a.x = (int)(pos.x / SCALE) * SCALE + SCALE;
	a.y = (pos.x - a.x) * -tan(deg_to_rad(angle)) + pos.y;
	return (a);
}

t_dxy	get_inc(double angle, int side, int dir)
{
	t_dxy	inc;

	if (side == HORIZONTAL)
	{
		if (dir == UP)
			inc.y = -SCALE;
		else // down
			inc.y = SCALE;
		inc.x = inc.y / tan(deg_to_rad(angle));
	}
	else // VERTICAL
	{
		if (dir == LEFT)
			inc.x = -SCALE;
		else // RIGHT
			inc.x = SCALE;
		inc.y = inc.x * tan(deg_to_rad(angle));
	}
	return (inc);
}

double	dda(t_map *map, double angle, t_dxy a, int side, int dir) // is this even dda?? I doubt it
{
	t_dxy	inc; // the distance to increment to check the next grid point

	inc = get_inc(angle, side, dir);
	while (1)
	{
		// mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, a.x, a.y, RED);
		// if ((int)(a.x / SCALE) < 0 || (int)(a.y / SCALE) < 0 || map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '\0' || map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '\n')
		if ((int)(a.x / SCALE) < 0 || (int)(a.y / SCALE) < 0 || (int)(a.x / SCALE) > 4 || (int)(a.y / SCALE) > 4)
			return (1e30);
		if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		{
			if (DEBUG)
			{
				if (side == VERTICAL)
					line(*map, map->player.pos.x, map->player.pos.y, a.x, a.y, BLUE);
				if (side == HORIZONTAL)
			 		line(*map, map->player.pos.x, map->player.pos.y, a.x, a.y, GREEN);
			}
			break ;
		}
		a.x += inc.x; // next x-axis pos on the grid
		a.y += inc.y; // next y-axis pos on the grid
	}
	return (get_dst(map->player.pos, a)); 
}

double	rays(t_map *map, double angle)
{
	int		side; // side of the ray (UP or Down) for the horizontal grid and (LEFT or RIGHT) for vertical grid
	t_dxy	hpoint; // first horizontal grid point according to the 2d map
	t_dxy	vpoint; // first vertical grid point according to the 2d map
	double	hray_dst; // horizontal ray distance between the player and the wall
	double	vray_dst; // vertical ray distance between the player and the wall

	hray_dst = 1e30;
	vray_dst = 1e30;
	if (angle != 180.0 && angle != 0.0)
	{
		side = angle_side(angle, HORIZONTAL); // UP or DOWN
		hpoint = first_hpoint(map->player.pos, angle, side); // first hoirzontal grid point
		hray_dst = dda(map, angle, hpoint, HORIZONTAL, side); // horizontal grid points
	}
	if (angle != 90.0 && angle != 270.0)
	{
		side = angle_side(angle, VERTICAL); // LEFT or RIGHT
		vpoint = first_vpoint(map->player.pos, angle, side); // first vertical grid point
		vray_dst = dda(map, angle, vpoint, VERTICAL, side); // vertical grid points
	}
	if (hray_dst < vray_dst) // check which ray is shorter to use its dst
		return (hray_dst);
	else
		return (vray_dst);
}

double	fishazz(double ray_dst, double angle, double org_angle) // WIP
{
	// if (angle > 0 && angle < 90)
	// 	return (cos(deg_to_rad(180 - angle)) * ray_dst);
	// else if (angle > 90 && angle < 180)
	// 	return (cos(deg_to_rad(angle - 90)) * ray_dst);
	// else if (angle > 180 && angle < 270)
	// 	return (cos(deg_to_rad(270 - angle)) * ray_dst);
	// else if (angle > 270 && angle < 360)
	// 	return (cos(deg_to_rad(angle - 270)) * ray_dst);
	// else
	// 	return(ray_dst);
	return (cos(deg_to_rad(org_angle - angle)) * ray_dst);
}

double	om_eldonia(t_map *map, double angle);

double get_values(t_map *map, double angle)
{
	double	ray_dst;

	ray_dst = rays(map, angle);
	// ray_dst = om_eldonia(map, angle);
	ray_dst = fishazz(ray_dst, angle, map->player.angle);
	ray_dst = (SCALE * HEIGHT / 2) / ray_dst;
	if (ray_dst > HEIGHT)
		ray_dst = HEIGHT;
	return (ray_dst);
}

double	om_eldonia(t_map *map, double angle)
{
	int		side;
	t_dxy	hpoint;
	t_dxy	vpoint;
	t_dxy	hinc;
	t_dxy	vinc;
	t_dxy	track;

	side = angle_side(angle, HORIZONTAL);
	hpoint = first_hpoint(map->player.pos, angle, side);
	hinc = get_inc(angle, HORIZONTAL, side);
	side = angle_side(angle, VERTICAL);
	vpoint = first_vpoint(map->player.pos, angle, side);
	vinc = get_inc(angle, VERTICAL, side);
	track.x = fabs(hinc.x);
	track.y = fabs(vinc.y);
	// track.x = fabs(map->player.pos.x - hpoint.x);
	// track.y = fabs(map->player.pos.y - vpoint.y);
	int hit = 0;
	int chance = 0;
	while (!hit || !chance)
	{
		if (hit)
			chance = 1;
		if (fabs(track.x) <= fabs(track.y))
		{
			if (map->map[(int)(hpoint.y / SCALE)][(int)(hpoint.x / SCALE)] == '1')
				hit = 1;
			else
			{
				hpoint.x += hinc.x;
				hpoint.y += hinc.y;
				track.x += fabs(hinc.x);
			}
		}
		if (fabs(track.y) <= fabs(track.x))
		{
			if (map->map[(int)(vpoint.y / SCALE)][(int)(vpoint.x / SCALE)] == '1')
				hit = 1;
			else
			{
				vpoint.x += vinc.x;
				vpoint.y += vinc.y;
				track.y += fabs(vinc.y);
			}
		}
	}
	if (get_dst(map->player.pos, hpoint) < get_dst(map->player.pos, vpoint))
	{
		line(*map, map->player.pos.x, map->player.pos.y, hpoint.x, hpoint.y, BLUE);
		return (get_dst(map->player.pos, hpoint));
	}
	else
	{
		line(*map, map->player.pos.x, map->player.pos.y, vpoint.x, vpoint.y, GREEN);
		return (get_dst(map->player.pos, vpoint));
	}
}
