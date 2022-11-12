/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2022/11/12 23:27:32 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_map *map)
{
	if (key == 13)
		map->player.pos.y++;
	else if (key == 1)
		map->player.pos.y--;
	else if (key == 0)
		map->player.pos.x--;
	else if (key == 2)
		map->player.pos.x++;
	return (SUCCESS);
}

void	init_struct(t_map *map)
{
	map->time = 0;
	map->old_time = 0;
	map->player.pos.x = 22;
	map->player.pos.y = 12;
	map->player.dir.x = -1;
	map->player.dir.y = 0;
	map->player.render.plane.x = 0;
	map->player.render.plane.y = 0.66;
}

void	draw_image(t_map *map, int x)
{
	while (map->player.render.draw.x < map->player.render.draw.y)
	{
		mlx_pixel_put(map->mlx.mlx, map->mlx.win,
			x, map->player.render.draw.x, 0x88CDF6);
		map->player.render.draw.x++;
	}
	return ;
}

int	render_loop(t_map *map)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		get_values(map, x);
		draw_image(map, x);
		x++;
	}
	// printf("x: %f - y: %f\n", map->player.pos_x, map->player.pos_y);
	return (SUCCESS);
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
	load_assets(map);
	map.mlx.win = mlx_new_window(map.mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx_loop_hook(map.mlx.mlx, render_loop, &map);
	mlx_hook(map.mlx.win, ON_KEYDOWN, 0, &keys, &map);
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
