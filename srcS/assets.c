#include "cub3d.h"

void	load_assets(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map->tex[i].img.frame = mlx_xpm_file_to_image(\
			map->mlx.mlx, map->tex[i].path, \
			&map->tex[i].img_width, &map->tex[i].img_height);
		map->tex[i].img.data = (int *)mlx_get_data_addr(\
			map->tex[i].img.frame, &map->tex[i].img.bpp, \
			&map->tex[i].img.size_line, &map->tex[i].img.endian);
		i++;
	}
	return ;
}
