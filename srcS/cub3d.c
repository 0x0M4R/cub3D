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

void	draw_square(t_map map, int x1, int y1)
{
	int		x2;
	int		y2;

	y2 = y1;
	while (y2 < y1 + 100 && y2 < HEIGHT)
	{
		x2 = x1;
		while (x2 < x1 + 100 && x2 < WIDTH)
		{
			mlx_pixel_put(map.mlx.mlx, map.mlx.win, x1, y1, 0x88CDF6);
			x2++;
		}
		y2++;
	}
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
	map.mlx.win = mlx_new_window(map.mlx.mlx, 1920, 1080, "cub3d");
	draw_square(map, 500, 500);
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
