/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2022/11/13 18:41:55 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_map *map)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == 13)
	{
		map->player.pos.x += map->player.dir.x * SPEED;
		map->player.pos.y += map->player.dir.y * SPEED;
	}
	else if (key == 1)
	{
		map->player.pos.x -= map->player.dir.x * SPEED;
		map->player.pos.y -= map->player.dir.y * SPEED;
	}
	else if (key == 0)
	{
		old_dir_x = map->player.dir.x;
		map->player.dir.x = map->player.dir.x * cos(SPEED) - map->player.dir.y * sin(SPEED);
		map->player.dir.y = old_dir_x * sin(SPEED) + map->player.dir.y * cos(SPEED);
		old_plane_x = map->player.render.plane.x;
		map->player.render.plane.x = map->player.render.plane.x * cos(SPEED) - map->player.render.plane.y * sin(SPEED);
		map->player.render.plane.y = old_plane_x * sin(SPEED) + map->player.render.plane.y * cos(SPEED);
	}
	else if (key == 2)
	{
		old_dir_x = map->player.dir.x;
		map->player.dir.x = map->player.dir.x * cos(-SPEED) - map->player.dir.y * sin(-SPEED);
		map->player.dir.y = old_dir_x * sin(-SPEED) + map->player.dir.y * cos(-SPEED);
		old_plane_x = map->player.render.plane.x;
		map->player.render.plane.x = map->player.render.plane.x * cos(-SPEED) - map->player.render.plane.y * sin(-SPEED);
		map->player.render.plane.y = old_plane_x * sin(-SPEED) + map->player.render.plane.y * cos(-SPEED);
	}
	return (SUCCESS);
}

void	find_player(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSEW", map->map[i][j]))
			{
				map->player.pos.x = i;
				map->player.pos.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_struct(t_map *map)
{
	find_player(map);
	map->time = 0;
	map->old_time = 0;
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
			x, map->player.render.draw.x, map->player.render.color);
		map->player.render.draw.x++;
	}
	return ;
}

int	render_loop(t_map *map)
{
	int		x;

	x = 0;
	mlx_clear_window(map->mlx.mlx, map->mlx.win);
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
