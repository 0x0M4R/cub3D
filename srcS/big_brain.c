/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/03 18:44:18 by ommohame         ###   ########.fr       */
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

double	dda(t_map *map, double angle, t_dxy a, int side, int dir) // is this even dda?? I doubt it
{
	t_dxy	inc; // the distance to increment to check the next grid point

	inc = get_inc(angle, side, dir);
	while (1)
	{
		// if (side == HORIZONTAL)
		// 	mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, a.x, a.y, GREEN);
		// else if (side == VERTICAL)
		// 	mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, a.x, a.y, BLUE);
		// if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		if ((int)(a.x / SCALE) < 0 || (int)(a.x / SCALE) > 4 || (int)(a.y / SCALE) < 0 || (int)(a.y / SCALE) > 4)
			return (1e30);
		if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		{
			if (side == VERTICAL)
				line(*map, map->player.pos.x, map->player.pos.y, a.x, a.y, BLUE);
			else
				line(*map, map->player.pos.x, map->player.pos.y, a.x, a.y, GREEN);
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

double	fishazz(double ray_dst, double angle) // WIP
{
	double	angleito; // the angle between the ray and the player plane

	(void)angle;
	(void)angleito;
	return (ray_dst * cos(deg_to_rad(angle)));
}

double	baqalaa(t_map *map, double angle);
double	baqalaa_v2(t_map *map, double angle);
double	supermarket(t_map *map, double angle);
double	wahda_mall(t_map *map, double angle);
double	abudhabi_mall(t_map *map, double angle);
double	uae(t_map *map, double angle);

double get_values(t_map *map, double angle)
{
	// double	hray;
	// double	vray;
	double	ray_dst;

	ray_dst = rays(map, angle);
	// ray_dst = baqalaa(map, angle);
	// ray_dst = baqalaa_v2(map, angle);
	// ray_dst = supermarket(map, angle);
	// hray = wahda_mall(map, angle);
	// vray = abudhabi_mall(map, angle);
	// if (hray < vray)
		// ray_dst = hray;
	// else
	// 	ray_dst = vray;
	// ray_dst = fishazz(ray_dst, angle);
	ray_dst = (SCALE * HEIGHT / 2) / ray_dst;
	if (ray_dst > HEIGHT)
		ray_dst = HEIGHT;
	return (ray_dst);
}

// double uae(t_map *map, double angle)
// {
// 	t_dxy	hpoint;
// 	t_dxy	vpoint;
// }

double wahda_mall(t_map *map, double angle) // FUNCTION UNDER CONSTRUCTION
{
	int		side;
	int		step;
	double	dx;
	double	dy;
	t_dxy	point;
	t_dxy	hpoint;
	t_dxy	inc;

	if (angle == 0 || angle == 180)
		return (1e30);
	side = angle_side(angle, HORIZONTAL);
	hpoint = first_hpoint(map->player.pos, angle, side);
	dx = map->player.pos.x - hpoint.x;
	dy = map->player.pos.y - hpoint.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	inc.x = dx / step;
	inc.y = dy / step;
	inc = get_inc(angle, HORIZONTAL, side);
	point.x = map->player.pos.x;
	point.y = map->player.pos.y;
	while (1)
	{
		mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, point.x, point.y, GREEN);
		if (map->map[(int)(point.y / SCALE)][(int)(point.x / SCALE)] == '1')
		{
			// if (DEBUG)
				// line(*map, map->player.pos.x, map->player.pos.y, point.x, point.y, GREEN);
			return (get_dst(map->player.pos, point));
		}
		point.x += inc.x;
		point.y += inc.y;
	}
}

double abudhabi_mall(t_map *map, double angle) // FUNCTION UNDER CONSTRUCTION
{
	int		side;
	int		step;
	double	dx;
	double	dy;
	t_dxy	point;
	t_dxy	vpoint;
	t_dxy	inc;

	if (angle == 270 || angle == 90)
		return (1e30);
	side = angle_side(angle, VERTICAL);
	vpoint = first_vpoint(map->player.pos, angle, side);
	dx = map->player.pos.x - vpoint.x;
	dy = map->player.pos.y - vpoint.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	inc.x = dx / step;
	inc.y = dy / step;
	point.x = map->player.pos.x;
	point.y = map->player.pos.y;
	while (1)
	{
		mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, point.x, point.y, BLUE);
		if (map->map[(int)(point.y / SCALE)][(int)(point.x / SCALE)] == '1')
		{
			// if (DEBUG)
				// line(*map, map->player.pos.x, map->player.pos.y, point.x, point.y, BLUE);
			return (get_dst(map->player.pos, point));
		}
		point.x += inc.x;
		point.y += inc.y;
	}
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
	hray_dst = get_dst(map->player.pos, hpoint); // horizontal grid points
	vray_dst = get_dst(map->player.pos, vpoint); // vertical grid points
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
		hray_dst = get_dst(map->player.pos, hpoint); // horizontal dst
		vray_dst = get_dst(map->player.pos, vpoint); // vertical dst
	}
}

double baqalaa_v2(t_map *map, double angle)
{
	double	dx;
	double	dy;
	t_dxy	hpoint; // first horizontal grid point according to the 2d map
	t_dxy	vpoint; // first vertical grid point according to the 2d map
	t_dxy	hinc;
	t_dxy	vinc;
	int		steps;
	int		x;
	int		y;

	hpoint = first_hpoint(map->player.pos, angle, angle_side(angle, HORIZONTAL)); // first hoirzontal grid point
	vpoint = first_vpoint(map->player.pos, angle, angle_side(angle, VERTICAL)); // first vertical grid point
	hinc = get_inc(angle, HORIZONTAL, angle_side(angle, HORIZONTAL));
	vinc = get_inc(angle, VERTICAL, angle_side(angle, VERTICAL));
	dx = map->player.pos.x - hpoint.x;
	dy = map->player.pos.y - hpoint.y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x = hpoint.x;
	y = vpoint.y;
	while (1)
	{
		if (map->map[(int)(y / SCALE)][(int)(x / SCALE)] == '1')
			return (get_dst(map->player.pos, (t_dxy){x, y}));
		x += hinc.x;
		y += vinc.y;
	}
}

double	supermarket(t_map *map, double angle)
{
	int		side;
	int		hside;
	int		vside;
	int		count;
	t_dxy	hpoint;
	t_dxy	vpoint;
	t_dxy	hinc;
	t_dxy	vinc;
	

	hside = angle_side(angle, HORIZONTAL);
	vside = angle_side(angle, VERTICAL);
	hpoint = first_hpoint(map->player.pos, angle, hside);
	vpoint = first_vpoint(map->player.pos, angle, vside);
	hinc = get_inc(angle, HORIZONTAL, hside);
	vinc = get_inc(angle, VERTICAL, vside);
	if (fabs(hinc.x) < fabs(vinc.y))
	{
		side = HORIZONTAL;
		count = fabs(vinc.y / hinc.x);
	}
	else
	{
		side = VERTICAL;
		count = fabs(hinc.x / vinc.y);
	}
	if (side == HORIZONTAL)
	{
		while (1)
		{
			for (int i = 0; i < count; i++)
			{
				if (map->map[(int)(hpoint.y / SCALE)][(int)(hpoint.x / SCALE)] == '1')
					return (get_dst(map->player.pos, hpoint));
				hpoint.x += hinc.x;
				hpoint.y += hinc.y;
			}
			if (map->map[(int)(vpoint.y / SCALE)][(int)(vpoint.x / SCALE)] == '1')
				return (get_dst(map->player.pos, vpoint));
			vpoint.x += vinc.x;
			vpoint.y += vinc.y;
		}
	}
	else
	{
		while (1)
		{
			for (int i = 0; i < count; i++)
			{
				if (map->map[(int)(vpoint.y / SCALE)][(int)(vpoint.x / SCALE)] == '1')
					return (get_dst(map->player.pos, vpoint));
				vpoint.x += vinc.x;
				vpoint.y += vinc.y;
			}
			if (map->map[(int)(hpoint.y / SCALE)][(int)(hpoint.x / SCALE)] == '1')
				return (get_dst(map->player.pos, hpoint));
			hpoint.x += hinc.x;
			hpoint.y += hinc.y;
		}
	}
}
