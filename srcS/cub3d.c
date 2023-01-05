/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/05 16:45:00 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_map *map)
{
	find_player(map);
	load_assets(map);
}

int	init_cube(char **av)
{
	t_map	map;

	parse_map(av[1], &map);
	init_struct(&map);
	map.mlx.mlx = mlx_init();
	if (!map.mlx.mlx)
	{
		ft_putstr_fd("Cube3D: Error: Failed to init minishell.\n", 2);
		return (ERROR);
	}
	map.mlx.win = mlx_new_window(map.mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (DEBUG)
		map.mlx.tmp = mlx_new_window(map.mlx.mlx, 5 * 64, 5 * 64, "debug");
	mlx_loop_hook(map.mlx.mlx, game_loop, &map);
	mlx_hook(map.mlx.win, ON_KEYDOWN, 0, &keys, &map);
	mlx_loop(map.mlx.mlx);
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
		ret = init_cube(av);
	if (ret == ERROR)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
