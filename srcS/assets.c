#include "cub3d.h"

int	load_assets(void *mlx_ptr, t_textures *tex)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tex->walls[i] = (t_frame *)malloc(sizeof(t_frame));
		if (!tex->walls[i])
			return (ft_putstr_fd(MALLOC_ERROR, 2) ,ERROR);
		tex->walls[i]->frame = mlx_xpm_file_to_image(mlx_ptr,
				tex->walls_path[i],
				&tex->walls[i]->img_width, &tex->walls[i]->img_height);
		tex->walls[i]->data = (int *)mlx_get_data_addr(
				tex->walls[i]->frame, &tex->walls[i]->bpp,
				&tex->walls[i]->size_line, &tex->walls[i]->endian);
		i++;
	}
	return (SUCCESS);
}
