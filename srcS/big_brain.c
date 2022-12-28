/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/28 22:21:27 by ommohame         ###   ########.fr       */
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
			return (RIGHT);
		else
			return (LEFT);
	}
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

double dda(t_map *map, double angle, t_dxy a, int side, int dir) // is this even dda?? I doubt it
{
	t_dxy	inc; // the distance to increment to check the next grid point
	double	dst; // ray distance to the wall
	// t_dxy	b; // the new grid point after a on the 2d grid

	inc = get_inc(angle, side, dir);
	while (1)
	{
		// if (side == VERTICAL)
			// printf("vert a.x %d - a.y %d, inc.x %d - inc.y %d, angle: %f\n", (int)a.x / SCALE, (int)a.y / SCALE, (int)inc.x / SCALE, (int)inc.y / SCALE, angle); 
		// else
		// 	printf("horz a.x %d - a.y %d, inc.x %d - inc.y %d\n", (int)a.x / SCALE, (int)a.y / SCALE, (int)inc.x / SCALE, (int)inc.y / SCALE);
		if (side == VERTICAL)
			mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, a.x, a.y, BLUE);
		else
			mlx_pixel_put(map->mlx.mlx, map->mlx.tmp, a.x, a.y, GREEN);
		if ((a.y / SCALE) < 0 || (a.y / SCALE) > 4 || (a.x / SCALE) < 0 || (a.x / SCALE) > 4 || map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		// if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		{
			// printf("break\n");
			break ;
		}
		// printf("after checking\n");
		a.x += inc.x; // next x-axis pos on the grid
		a.y += inc.y; // next y-axis pos on the grid
	}
	dst = sqrt(pow(map->player.pos.x - a.x, 2) + pow(map->player.pos.y - a.y, 2));
	return (dst);
}


double baqlaa(t_map *map, double angle)
{
	int 	hside;
	int 	vside;
	t_dxy	hpoint1; // first horizontal grid point according to the 2d map
	t_dxy	vpoint1; // first vertical grid point according to the 2d map
	t_dxy	hpoint2; // first horizontal grid point according to the 2d map
	t_dxy	vpoint2; // first vertical grid point according to the 2d map
	t_dxy	hinc;
	t_dxy	vinc;

	hside = angle_side(angle, HORIZONTAL); // UP or DOWN
	hpoint1 = first_hpoint(map, angle, hside); // first hoirzontal grid point
	vside = angle_side(angle, VERTICAL); // LEFT or RIGHT
	vpoint1 = first_vpoint(map, angle, vside); // first vertical grid point
	hinc = get_inc(angle, HORIZONTAL, hside);
	vinc = get_inc(angle, VERTICAL, vside);
	while (1)
	{
		hpoint2.x = hpoint1.x + hinc.x;
		hpoint2.y = hpoint1.y + hinc.y;
		vpoint2.x = vpoint1.x + vinc.x;
		vpoint2.y = vpoint1.y + vinc.y;
		if (map->map[(int)(vpoint2.y / SCALE)][(int)(vpoint2.x / SCALE)] == '1')
			return (sqrt(pow(map->player.pos.x - vpoint2.x, 2) + pow(map->player.pos.y - vpoint2.y, 2)));
		else if (map->map[(int)(hpoint2.y / SCALE)][(int)(hpoint2.x / SCALE)] == '1')
			return (sqrt(pow(map->player.pos.x - hpoint2.x, 2) + pow(map->player.pos.y - hpoint2.y, 2)));
		hpoint1.x = hpoint2.x;
		hpoint1.y = hpoint2.y;
		vpoint1.x = vpoint2.x;
		vpoint1.y = vpoint2.y;
	}
	return (0);
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
	// if (hray_dst < vray_dst) // check which ray is shorter to use its dst
		return (hray_dst);
	// else
	// 	return (vray_dst);
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
	// ray_dst = baqlaa(map, angle);
	map->player.render.height = ray_dst;
	// printf("dst of angele %1f: %1f\n", angle, ray_dst);
	// map->player.render.height = fishazz(ray_dst, angle); // fix for the fisheye effect
	return ;
}
