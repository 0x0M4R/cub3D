#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (ac != 2)
	{
		write(1, "Error\nWrong number of arguments.\n", 34);
		exit(0);
	}
	parse_map(av[1], map);
}