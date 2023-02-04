/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:55:00 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/05 02:58:21 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_mlx(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->texts->walls[i]->frame);
		mlx_destroy_image(data->mlx_ptr, data->texts->gun[i]->frame);
	}
	mlx_destroy_image(data->mlx_ptr, data->texts->gun[i]->frame);
	mlx_destroy_image(data->mlx_ptr, data->texts->door->frame);
}

static void	free_struct(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		free(data->texts->walls[i]);
		free(data->texts->gun[i]);
	}
	free(data->texts->gun[i]);
	free(data->texts->door);
	free(data->texts);
	free(data->player);
	free_2d(data->map->map);
	free(data->map);
	free(data->mlx_ptr);
	free(data);
}

int	ft_exit(t_data *data)
{
	destroy_mlx(data);
	free_struct(data);
	exit(EXIT_SUCCESS);
}
