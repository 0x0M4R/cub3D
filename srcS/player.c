/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:08:44 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 14:30:06 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_player_angle(char c)
{
	if (c == 'N')
		return (270.0);
	else if (c == 'S')
		return (90.0);
	else if (c == 'E')
		return (0.0);
	else
		return (180.0);
}


static void	player_pos_ang(t_player *player, char c, size_t i, size_t j)
{
	player->angle = get_player_angle(c);
	player->pos.y = (i * SCALE) + SCALE / 2;
	player->pos.x = (j * SCALE) + SCALE / 2;
}

t_player	*get_player(char **map)
{
	size_t		i;
	size_t		j;
	size_t		count;
	t_player	*player;

	i = -1;
	count = 0;
	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				player_pos_ang(player, map[i][j], i, j);
				count++;
			}
		}
	}
	if (count != 1)
		return (ft_putstr_fd(PLAYER_ERROR, 2), free(player), NULL);
	return (player);
}
