/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/22 22:31:11 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_map *map)
{
	if (key == 13) // forward
	{
		map->player.pos.y--;
	}
	else if (key == 1) //backward
	{
		map->player.pos.y++;
	}
	else if (key == 0) //left
	{
	}
	else if (key == 2) //right
	{
	}
	(void)map;
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
				map->player.angle = 90;
				map->player.pos.x = i;
				map->player.pos.y = j;
				map->player.map.x = i;
				map->player.map.x = j;
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
}

void	draw_image(t_map *map, int x)
{
	for (int i = HEIGHT / 2; i > map->player.render.height; i--)
		mlx_pixel_put(map->mlx.mlx, map->mlx.win, x, i, RED);
	(void)map;
	(void)x;
	return ;
}

int	render_loop(t_map *map)
{
	int		x; // column number
	double	angle; // angle of the first ray
	double	ang_inc; // the angle difference between each rays

	x = 0;
	mlx_clear_window(map->mlx.mlx, map->mlx.win);
	ang_inc = FOV / WIDTH;
	angle = map->player.angle - (FOV / 2);
	while (x < WIDTH)
	{
		printf("huh\n");
		get_values(map, angle);
		draw_image(map, x);
		x++;
		angle += ang_inc;
	}
	(void)map;
	(void)x;
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
