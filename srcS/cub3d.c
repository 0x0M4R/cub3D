/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 17:24:36 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_cube(char *map_path)
{
	t_data	*data;

	data = parser(map_path);
	if (!data)
		return (NULL);
	data->mlx_ptr = mlx_init();
	if (load_assets(data->mlx_ptr, data->texts) == ERROR)
	{
		return (free(data->player), free_2d(data->map->map),
			free(data->map), free(data), NULL);
	}
	if (!data->mlx_ptr)
	{
		ft_putstr_fd("Cube3D: Error: Failed to init minishell.\n", 2);
		return (NULL);
	}
	return (data);
}

int	cub3d(char *map_path)
{
	t_data	*data;

	data = init_cube(map_path);
	if (!data)
		return (ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
	mlx_hook(data->win_ptr, ON_KEYDOWN, 0, &keys, data);
	mlx_loop(data->mlx_ptr);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	int		ret;

	if (ac != 2)
	{
		ft_putstr_fd("Cub3D: Error: Wrong number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	else
		ret = cub3d(av[1]);
	if (ret == ERROR)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
