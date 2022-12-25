/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/25 21:15:42 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********** WIP *************/

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

double	deg_to_rad(int deg)
{
	return (deg * M_PI / (double)180);
}

t_dxy	first_hpoint(t_map *map, double angle, int side)
{
	t_dxy	a; //  first horizontal grid point according to the 2d map

	if (side == UP)
		a.y = (int)(map->player.pos.y / SCALE) * SCALE - 1;
	else if (side == DOWN)
		a.y = (int)(map->player.pos.y / SCALE) * SCALE + SCALE;
	a.x =  map->player.pos.x + (map->player.pos.y - a.y) / tan(deg_to_rad(angle));
	// a.x /= 64;
	// a.y /= 64;
	return (a);
}

t_dxy	first_vpoint(t_map *map, double angle, int side)
{
	t_dxy	a; //  first vertical grid point according to the 2d map

	if (side == LEFT)
		a.x = (int)(map->player.pos.x / SCALE) * SCALE - 1;
	else if (side == RIGHT)
		a.x = (int)(map->player.pos.x / SCALE) * SCALE + SCALE;
	a.y = map->player.pos.y + (map->player.pos.x - a.x) * tan(deg_to_rad(angle));
	// a.x /= 64;
	// a.y /= 64;
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

double dda(t_map *map, double angle, t_dxy a, int side, int dir)
{
	t_dxy	inc; // the distance to increment to check the next grid point
	double	dst; // ray distance to the wall
	// t_dxy	b; // the new grid point after a on the 2d grid

	inc = get_inc(angle, side, dir);
	for (int i = 0; i < 0; i++)
	{
		if (side == VERTICAL)
			printf("vert a.y: %f - a.x: %f, inc: %f\n", a.y / SCALE, a.x / SCALE, inc.y);
		else
			printf("horz a.y: %f - a.x: %f\n", a.y / SCALE, a.x / SCALE);
		if (map->map[(int)(a.x / SCALE)][(int)(a.y / SCALE)] == '1')
			break ;
		a.x += inc.x; // next x-axis pos on the grid
		a.y += inc.y; // next y-axis pos on the grid
	}
	dst = sqrt(pow(map->player.pos.x - a.x, 2) + pow(map->player.pos.y - a.y, 2));
	return (dst);
}

double	rays(t_map *map, double angle)
{
	int		side; // side of the ray (UP or Down) for the horizontal grid and (LEFT or RIGHT) for vertical grid
	t_dxy	hpoint; // first horizontal grid point according to the 2d map
	t_dxy	vpoint; // first vertical grid point according to the 2d map
	double	hray_dst; // horizontal ray distance between the player and the wall
	double	vray_dst; // vertical ray distance between the player and the wall

	side = angle_side(angle, HORIZONTAL); // UP or DOWN
	hpoint = first_hpoint(map, angle, side); // first hoirzontal grid point
	hray_dst = dda(map, angle, hpoint, HORIZONTAL, side); // horizontal grid points
	side = angle_side(angle, VERTICAL); // LEFT or RIGHT
	vpoint = first_vpoint(map, angle, side); // first vertical grid point
	vray_dst = dda(map, angle, vpoint, VERTICAL, side); // vertical grid points
	if (hray_dst < vray_dst) // check which ray is shorter to use its dst
		return (hray_dst);
	else
		return (vray_dst);
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

	ray_dst = rays(map, angle);
	map->player.render.height = ray_dst;
	// map->player.render.height = fishazz(ray_dst, angle); // fix for the fisheye effect
	return ;
}
