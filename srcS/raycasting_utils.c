/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:36:28 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 13:52:10 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_walls(t_map *map, t_dxy a)
{
	int		i;
	t_dxy	inc1[4];
	t_dxy	inc2[4];
	t_dxy	corner1;
	t_dxy	corner2;

	i = -1;
	if (check_map_range(map, a) == ERROR)
		return (SUCCESS);
	if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		return (SUCCESS);
	get_corners_inc(inc1, inc2);
	while (++i < 4)
	{
		corner1 = (t_dxy){a.x + inc1[i].x, a.y + inc1[i].y};
		corner2 = (t_dxy){a.x + inc2[i].x, a.y + inc2[i].y};
		if (check_map_range(map, corner1) == ERROR
			|| check_map_range(map, corner2) == ERROR)
			;
		else if (
			map->map[(int)(corner1.y / SCALE)][(int)(corner1.x / SCALE)] == '1'
		&& map->map[(int)(corner2.y / SCALE)][(int)(corner2.x / SCALE)] == '1')
			return (SUCCESS);
	}
	return (ERROR);
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
