/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/31 00:03:01 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********** WIP *************/

double	deg_to_rad(int deg)
{
	return (deg * M_PI / (double)180);
}

// get the angle quadrant for x-axis or y-axis
int		angle_side(double angle, int side)
{
	if (side == HORIZONTAL)
	{
		if (angle >= 0 && angle < 180)
			return (DOWN);
		else
			return (UP);
	}
	else // vertical
	{
		if (angle >= 90 && angle < 270)
			return (LEFT);
		else
			return (RIGHT);
	}
}

t_dxy	first_hpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a; //  first horizontal grid point according to the 2d map

	if (side == UP)
		a.y = (int)(pos.y / SCALE) * SCALE - 1;
	else if (side == DOWN)
		a.y = (int)(pos.y / SCALE) * SCALE + SCALE;
	a.x = (pos.y - a.y) / -tan(deg_to_rad(angle)) + pos.x;
	return (a);
}

t_dxy	first_vpoint(t_dxy pos, double angle, int side)
{
	t_dxy	a; //  first vertical grid point according to the 2d map

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

double	get_dst(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double	dda(t_map *map, double angle, t_dxy a, int side, int dir) // is this even dda?? I doubt it
{
	t_dxy	inc; // the distance to increment to check the next grid point

	inc = get_inc(angle, side, dir);
	while (1)
	{
		// if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		if ((int)(a.x / SCALE) < 0 || (int)(a.x / SCALE) >= 4 || (int)(a.y / SCALE) < 0 || (int)(a.y / SCALE) >= 4 || map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		{
			// if (side == HORIZONTAL)
			// 	line(*map, map->player.pos.x, map->player.pos.y, a.x, a.y);
			break ;
		}
		a.x += inc.x; // next x-axis pos on the grid
		a.y += inc.y; // next y-axis pos on the grid
	}
	return (get_dst(map->player.pos.x, map->player.pos.y, a.x, a.y)); 
}

double	rays(t_map *map, double angle)
{
	int		side; // side of the ray (UP or Down) for the horizontal grid and (LEFT or RIGHT) for vertical grid
	t_dxy	hpoint; // first horizontal grid point according to the 2d map
	t_dxy	vpoint; // first vertical grid point according to the 2d map
	double	hray_dst; // horizontal ray distance between the player and the wall
	double	vray_dst; // vertical ray distance between the player and the wall

	side = angle_side(angle, HORIZONTAL); // UP or DOWN
	hpoint = first_hpoint(map->player.pos, angle, side); // first hoirzontal grid point
	hray_dst = dda(map, angle, hpoint, HORIZONTAL, side); // horizontal grid points
	side = angle_side(angle, VERTICAL); // LEFT or RIGHT
	vpoint = first_vpoint(map->player.pos, angle, side); // first vertical grid point
	vray_dst = dda(map, angle, vpoint, VERTICAL, side); // vertical grid points
	if (hray_dst < vray_dst) // check which ray is shorter to use its dst
		return (hray_dst);
	else
		return (vray_dst);
}

double	baqalaa(t_map *map, double angle)
{
	int		hside; // side of the ray (UP or Down) for the horizontal grid and (LEFT or RIGHT) for vertical grid
	int		vside; // side of the ray (UP or Down) for the horizontal grid and (LEFT or RIGHT) for vertical grid
	t_dxy	hpoint; // first horizontal grid point according to the 2d map
	t_dxy	vpoint; // first vertical grid point according to the 2d map
	double	hray_dst; // horizontal ray distance between the player and the wall
	double	vray_dst; // vertical ray distance between the player and the wall
	t_dxy	hinc;
	t_dxy	vinc;

	hside = angle_side(angle, HORIZONTAL); // UP or DOWN
	vside = angle_side(angle, VERTICAL); // LEFT or RIGHT
	hpoint = first_hpoint(map->player.pos, angle, hside); // first hoirzontal grid point
	vpoint = first_vpoint(map->player.pos, angle, vside); // first vertical grid point
	hray_dst = get_dst(map->player.pos.x, map->player.pos.y, hpoint.x, hpoint.y); // horizontal grid points
	vray_dst = get_dst(map->player.pos.x, map->player.pos.y, vpoint.x, vpoint.y); // vertical grid points
	hinc = get_inc(angle, HORIZONTAL, hside);
	vinc = get_inc(angle, VERTICAL, vside);
	while (1)
	{
		if (hray_dst < vray_dst)
		{
			if (map->map[(int)(hpoint.y / SCALE)][(int)(hpoint.x / SCALE)] == '1')
				return (hray_dst);
			else if (map->map[(int)(vpoint.y / SCALE)][(int)(vpoint.x / SCALE)] == '1')
				return (vray_dst);
		}
		else
		{
			if (map->map[(int)(vpoint.y / SCALE)][(int)(vpoint.x / SCALE)] == '1')
				return (vray_dst);
			else if (map->map[(int)(hpoint.y / SCALE)][(int)(hpoint.x / SCALE)] == '1')
				return (hray_dst);
		}
		hpoint.x += hinc.x; // next x-axis pos on the grid
		hpoint.y += hinc.y; // next y-axis pos on the grid
		vpoint.x += vinc.x; // next x-axis pos on the grid
		vpoint.y += vinc.y; // next y-axis pos on the grid
		hray_dst = get_dst(map->player.pos.x, map->player.pos.y, hpoint.x, hpoint.y); // horizontal grid points
		vray_dst = get_dst(map->player.pos.x, map->player.pos.y, vpoint.x, vpoint.y); // vertical grid points
	}
}

double	fishazz(double ray_dst, double angle) // WIP
{
	double	angleito; // the angle between the ray and the player plane

	angleito = 90 - angle; // not accurate yet
	return (ray_dst * cos(deg_to_rad(angleito)));
}

void	get_values(t_map *map, double angle)
{
	double	ray_dst;

	// ray_dst = rays(map, angle);
	ray_dst = baqalaa(map, angle);
	ray_dst = (SCALE * HEIGHT) / ray_dst;
	map->player.render.height = ray_dst;
	// printf("dst of angele %1f: %1f\n", angle, ray_dst);
	// map->player.render.height = fishazz(ray_dst, angle); // fix for the fisheye effect
	return ;
}
