#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
	{
		write(1, "Error\nWrong number of arguments.\n", 34);
		exit(0);
	}
	parse_map(av[1], &map);
	map.mlx.mlx = mlx_init();
	map.mlx.win = mlx_new_window(map.mlx.mlx, 1920, 1080, "cub3d");
	mlx_loop(map.mlx.mlx);
}