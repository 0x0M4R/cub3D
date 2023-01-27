/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:38:59 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/27 12:11:17 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	invalid_asset(void *mlx_ptr, t_textures *tex, int i)
{
	int		j;

	j = -1;
	while (++j < i - 1 && j < 4)
		mlx_destroy_image(mlx_ptr, tex->walls[j]->frame);
	while (i < 4)
	{
		free(tex->walls_path[i]);
		i++;
	}
	ft_putstr_fd(TEXTURE_ERROR, 2);
}

int	get_door(void *mlx_ptr, t_textures *tex)
{
	tex->door = (t_frame *)malloc(sizeof(t_frame));
	if (!tex->door)
		return (ft_putstr_fd(MALLOC_ERROR, 2), FALSE);
	tex->door->frame = mlx_xpm_file_to_image(mlx_ptr,
			"xpms/alka.xpm",
			&tex->door->img_width, &tex->door->img_height);
	if (!tex->door->frame)
		return (FALSE);
	else
		tex->door->data = (int *)mlx_get_data_addr(
				tex->door->frame, &tex->door->bpp,
				&tex->door->size_line, &tex->door->endian);
	return (TRUE);
}

int	load_assets(void *mlx_ptr, t_textures *tex)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (i < 4 && !err)
	{
		tex->walls[i] = (t_frame *)malloc(sizeof(t_frame));
		if (!tex->walls[i])
			return (ft_putstr_fd(MALLOC_ERROR, 2), FALSE);
		tex->walls[i]->frame = mlx_xpm_file_to_image(mlx_ptr,
				tex->walls_path[i],
				&tex->walls[i]->img_width, &tex->walls[i]->img_height);
		if (!tex->walls[i]->frame)
			err = 1;
		else
			tex->walls[i]->data = (int *)mlx_get_data_addr(
					tex->walls[i]->frame, &tex->walls[i]->bpp,
					&tex->walls[i]->size_line, &tex->walls[i]->endian);
		free(tex->walls_path[i]);
		i++;
	}
	if (err || get_door(mlx_ptr, tex) == FALSE)
		return (invalid_asset(mlx_ptr, tex, i), FALSE);
	return (TRUE);
}
