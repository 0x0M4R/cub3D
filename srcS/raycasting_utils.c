/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:05:32 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 17:40:41 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_range(t_map *map, t_dxy point)
{
	if (point.x < 0)
		return (FALSE);
	if (point.y < 0)
		return (FALSE);
	if (point.x > (map->width - 1) * SCALE)
		return (FALSE);
	if (point.y > (map->height - 1) * SCALE)
		return (FALSE);
	return (TRUE);
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
	if (check_map_range(map, a) == FALSE)
		return (TRUE);
	if (map->map[(int)(a.y / SCALE)][(int)(a.x / SCALE)] == '1')
		return (TRUE);
	get_corners_inc(inc1, inc2);
	while (++i < 4)
	{
		corner1 = (t_dxy){a.x + inc1[i].x, a.y + inc1[i].y};
		corner2 = (t_dxy){a.x + inc2[i].x, a.y + inc2[i].y};
		if (check_map_range(map, corner1) == FALSE
			|| check_map_range(map, corner2) == FALSE)
			;
		else if (
			map->map[(int)(corner1.y / SCALE)][(int)(corner1.x / SCALE)] == '1'
		&& map->map[(int)(corner2.y / SCALE)][(int)(corner2.x / SCALE)] == '1')
			return (TRUE);
	}
	return (FALSE);
}
