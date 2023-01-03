/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:19:21 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/03 12:29:04 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_player_angle(char c)
{
	if (c == 'N')
		return (270);
	else if (c == 'S')
		return (90);
	else if (c == 'E')
		return (0);
	else
		return (180);
}

void	find_player(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSEW", map->map[i][j]))
			{
				map->player.angle = get_player_angle(map->map[i][j]);
				map->player.pos.y = (i * SCALE) + SCALE / 2;
				map->player.pos.x = (j * SCALE) + SCALE / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}
