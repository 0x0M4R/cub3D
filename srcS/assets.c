#include "cub3d.h"

void	load_assets(t_map *map)
{
	map->n_texture.image.frame = mlx_xpm_file_to_image
		(map->mlx.mlx, map->n_texture.path, &map->n_texture.img_width, &map->n_texture.img_height);
	map->n_texture.image.data = (int*)mlx_get_data_addr(
		map->n_texture.image.frame, &map->n_texture.image.bpp, &map->n_texture.image.size_line, &map->n_texture.image.endian);
	return ;
}
