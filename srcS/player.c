/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:08:44 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 23:08:45 by ommohame         ###   ########.fr       */
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

t_player	*get_player(char **map)
{
	int			i;
	int			j;
	t_player	*player;

	i = 0;
	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL); // error msg
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				player->angle = get_player_angle(map[i][j]);
				player->pos.y = (i * SCALE) + SCALE / 2;
				player->pos.x = (j * SCALE) + SCALE / 2;
				return (player);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
