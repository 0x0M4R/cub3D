/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:55:00 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/29 15:19:19 by ommohame         ###   ########.fr       */
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
	//mlx_destroy_window(data->mlx_ptr, data->win_ptr);
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
