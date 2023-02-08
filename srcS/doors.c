/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:23:19 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/27 17:34:54 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_door(t_data *data, t_dxy *point)
{
	int		i;
	char	c;
	t_dxy	inc;

	i = -1;
	inc.x = (cos(deg_to_rad(data->player->angle)) * SCALE / 8);
	inc.y = (sin(deg_to_rad(data->player->angle)) * SCALE / 8);
	while (++i < 8)
	{
		point->x += inc.x;
		point->y += inc.y;
		c = data->map->map[(int)(point->y / SCALE)][(int)(point->x / SCALE)];
		if (c == 'C')
			return (CLOSE);
		else if (c == 'O')
			return (OPEN);
	}
	return (NOT);
}

int	doors(t_data *data)
{
	int		state;
	t_dxy	point;

	point.x = data->player->pos.x;
	point.y = data->player->pos.y;
	state = check_door(data, &point);
	if ((state == OPEN)
		&& data->map->map[(int)(data->player->pos.y / SCALE)]
		[(int)(data->player->pos.x / SCALE)] != 'O')
		data->map->map[(int)(point.y / SCALE)][(int)(point.x / SCALE)] = 'C';
	else if (state == CLOSE)
		data->map->map[(int)(point.y / SCALE)][(int)(point.x / SCALE)] = 'O';
	else
		return (FALSE);
	return (TRUE);
}
