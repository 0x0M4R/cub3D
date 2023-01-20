/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:05:32 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 23:06:52 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_range(t_map *map, t_dxy point)
{
	if (point.x < 0)
		return (ERROR);
	if (point.y < 0)
		return (ERROR);
	if (point.x > map->width * SCALE)
		return (ERROR);
	if (point.y > map->height * SCALE)
		return (ERROR);
	return (SUCCESS);
}
