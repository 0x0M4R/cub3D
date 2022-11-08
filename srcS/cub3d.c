/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2022/11/08 16:52:24 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_assets(t_map map)
{
	(void)map;
	return ;
}

void	get_values(t_map *map)
{
	(void)map;
	return ;
}

void	draw_image(t_map map)
{
	(void)map;
	return ;
}

int	render_loop(t_map *map)
{
	get_values(map);
	draw_image(*map);
	return (SUCCESS);
}

int	init_cube(char **av)
{
	t_map	map;

	parse_map(av[1], &map);
	map.mlx.mlx = mlx_init();
	if (!map.mlx.mlx)
	{
		ft_putstr_fd("Cube3D: Error: Failed to init minishell.\n", 2);
		return (ERROR);
	}
	load_assets(map);
	map.mlx.win = mlx_new_window(map.mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx_loop_hook(map.mlx.mlx, render_loop, &map);
	mlx_loop(map.mlx.mlx);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	int		ret;

	if (ac != 2)
	{
		ft_putstr_fd("Cube3D: Error: Wrong number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	else
		ret = init_cube(av);
	if (ret == ERROR)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
