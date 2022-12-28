/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:46:43 by ommohame          #+#    #+#             */
/*   Updated: 2022/12/28 20:41:12 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, t_map *map)
{
	if (key == 13) // forward
	{
		// map->player.pos.x += cos(map->player.angle) * SPEED;
		map->player.pos.y += sin(map->player.angle) * SPEED;
	}
	else if (key == 1) //backward
	{
		map->player.pos.y -= sin(map->player.angle) * SPEED;
		// map->player.pos.x -= cos(map->player.angle) * SPEED;
		// map->player.pos.y -= sin(map->player.angle) * SPEED;
	}
	else if (key == 0) //left
	{
		map->player.angle -= SPEED;
	}
	else if (key == 2) //right
	{
		map->player.angle += SPEED;
	}
	return (SUCCESS);
}

double	get_angle(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'W')
		return (180);
	else if (c == 'S')
		return (270);
	else
		return (0);
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
				map->player.angle = get_angle(map->map[i][j]);
				map->player.pos.x = (i * SCALE) + SCALE / 2;
				map->player.pos.y = (j * SCALE) + SCALE / 2;
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

double	fix_angle(double angle)
{
	if (angle < 0)
		return (angle + 360);
	else if (angle > 360)
		return (angle - 360);
	else
		return (angle);
}

int	game_loop(t_map *map)
{
	int		x; // column number
	double	angle; // angle of the first ray
	double	ang_inc; // the angle difference between each rays
	t_frame	frame;

	x = 0;
	angle = fix_angle(map->player.angle - (FOV / 2));
	ang_inc = (double)FOV / (double)WIDTH;
	frame = create_frame(&map->mlx);
	draw_map(*map);
	while (x < WIDTH)
	{
		get_values(map, angle);
		draw_frame(map, frame.data, x);
		angle = fix_angle(angle + ang_inc);
		x++;
	}
	mlx_clear_window(map->mlx.mlx, map->mlx.win);
	mlx_put_image_to_window(map->mlx.mlx, map->mlx.win, frame.frame, 0, 0);
	mlx_destroy_image(map->mlx.mlx, frame.frame);
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
	map.mlx.tmp = mlx_new_window(map.mlx.mlx, 5 * 64, 5 * 64, "tmp");
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
