#include "cub3d.h"

void	load_assets(t_map *map)
{
	map->n_texture.image.img = mlx_xpm_file_to_image
		(map->mlx.mlx, map->n_texture.path, &map->n_texture.img_width, &map->n_texture.img_height);
	map->n_texture.image.addr = mlx_get_data_addr(
		map->n_texture.image.img, &map->n_texture.image.bits_per_pixel, &map->n_texture.image.line_length, &map->n_texture.image.endian);
	return ;
}
