/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/24 16:16:50 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********** WIP *************/

# define SCALE 64
# define UP	1
# define DOWN -1
# define LEFT_SIDE -1
# define RIGHT_SIDE 1
# define TOP_SIDE 1
# define BOT_SIDE -1
# define VERTICAL 0
# define HORIZONTAL 1
// get the angle quadrant for x-axis or y-axis
int		angle_side(double angle, int axis)
{
	// for now it only checks if up and down
	(void)axis;
	if (angle > 0 && angle < 180)
		return (1);
	else
		return (-1);
}

double	deg_to_rad(int deg)
{
	return (deg * M_PI / (double)180);
}

double dda(t_map *map, double angle, t_dxy a, int side)
{
	t_dxy	inc; // the distance to increment to check the next grid point
	double	dst; // ray distance to the wall
	t_dxy	b; // the first grid point after a on the 2d grid

	if (side == HORIZONTAL)
	{
		inc.y = SCALE * side;
		inc.x = inc.y / tan(deg_to_rad(angle));
	}
	for (int i = 0; i < 10; i++)
	{
		b.x = a.x + inc.x;
		b.y = a.y + inc.y;
		// b.x /= SCALE;
		// b.y /= SCALE;
		if (map->map[(int)b.x / SCALE][(int)b.y / SCALE] == '1')
			break ;
		a.x = b.x;
		a.y = b.y;
	}
	dst = sqrt(pow(map->player.pos.x - b.x, 2) + pow(map->player.pos.y - b.y, 2));
	return (dst);
}

double	rays(t_map *map, double angle)
{
	t_dxy	a; // first horizontal grid point according to the 2d map
	// t_dxy	b; // first vertical grid point according to the 2d map
	int		side; // ray side (UP OR DOWN)
	int		hray_dst; // horizontal ray distance between the player and the wall
	// int		vray_dst; // vertical ray distance between the player and the wall

	side = angle_side(angle, 0);
	if (side == UP)
		a.y = (int)(map->player.pos.y / SCALE) * SCALE - 1;
	else if (side == DOWN)
		a.y = (int)(map->player.pos.y / SCALE) * SCALE + 64;
	a.x =  map->player.pos.x + (map->player.pos.y - a.y) / tan(deg_to_rad(angle));
	a.x /= SCALE;
	a.y /= SCALE;
	hray_dst = dda(map, angle, a, HORIZONTAL); // horizontal grid points
	// dda(dst, yp); // vertical grid points
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
	map->player.render.height = ray_dst;
	// map->player.render.height = fishazz(ray_dst, angle); // fix for the fisheye effect
	return ;
}
