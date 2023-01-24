/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/22 14:15:33 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	free_struct(t_data *data)
{
	free(data->texts->walls[0]);
	free(data->texts->walls[1]);
	free(data->texts->walls[2]);
	free(data->texts->walls[3]);
	free(data->texts);
	free(data->player);
	free_2d(data->map->map);
	free(data->map);
	free(data);
	exit(EXIT_SUCCESS);
}

int	init_cube(char *map_path)
{
	t_data	*data;

	data = parser(map_path);
	if (!data)
		return (ERROR);
	data->player = get_player(data->map->map); // add to the parser
	data->mlx_ptr = mlx_init();
	load_assets(data->mlx_ptr, data->texts); // need to move
	if (!data->mlx_ptr)
	{
		ft_putstr_fd("Cube3D: Error: Failed to init minishell.\n", 2);
		return (ERROR);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (DEBUG)
		data->tmp_win_ptr = mlx_new_window(data->mlx_ptr,
				data->map->width * SCALE, data->map->height * SCALE, "debug");
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
		ret = init_cube(av[1]);
	if (ret == ERROR)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
