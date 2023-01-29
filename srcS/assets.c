/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:38:59 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/29 16:27:14 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	invalid_asset(void *mlx_ptr, t_textures *tex, int i, int type)
{
	int			j;
	int			x;
	t_frame		**data;

	j = -1;
	if (type == 0)
	{
		data = tex->walls;
		x = 4;
	}
	else
	{
		data = tex->gun;
		x = 5;
	}
	while (++j < i - 1 && j < x)
	{
		mlx_destroy_image(mlx_ptr, data[j]->frame);
		if (data[i])
			free(data[j]);
	}
	while (i < 4 && type == 0)
		free(tex->walls_path[i++]);
	ft_putstr_fd(TEXTURE_ERROR, 2);
}

int	load_door(void *mlx_ptr, t_textures *tex)
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

char	*get_gun_path(int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(i);
	if (!tmp1)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	tmp2 = ft_strjoin("xpms/gun", tmp1);
	free(tmp1);
	if (!tmp2)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	tmp1 = ft_strjoin(tmp2, ".xpm");
	free(tmp2);
	if (!tmp1)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	return (tmp1);
}

int	load_gun(void *mlx_ptr, t_textures *tex)
{
	int		i;
	char	*path;

	i = -1;
	while (++i < 5)
	{
		path = get_gun_path(i);
		if (!path)
			return (ft_putstr_fd(MALLOC_ERROR, 2), FALSE);
		tex->gun[i] = (t_frame *)malloc(sizeof(t_frame));
		if (!tex->gun[i])
			return (ft_putstr_fd(MALLOC_ERROR, 2), FALSE);
		tex->gun[i]->frame = mlx_xpm_file_to_image(mlx_ptr,
				path, &tex->gun[i]->img_width, &tex->gun[i]->img_height);
		if (!tex->gun[i]->frame)
			return (invalid_asset(mlx_ptr, tex, i, 1),
				ft_putstr_fd(TEXTURE_ERROR, 2), FALSE);
		else
			tex->gun[i]->data = (int *)mlx_get_data_addr(
					tex->gun[i]->frame, &tex->gun[i]->bpp,
					&tex->gun[i]->size_line, &tex->gun[i]->endian);
		free(path);
	}
	return (TRUE);
}

int	load_walls(void *mlx_ptr, t_textures *tex)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (i < 4 && !err)
	{
		tex->walls[i] = NULL;
		tex->walls[i] = (t_frame *)malloc(sizeof(t_frame));
		if (!tex->walls[i])
			return (ft_putstr_fd(MALLOC_ERROR, 2), FALSE);
		tex->walls[i]->frame = mlx_xpm_file_to_image(mlx_ptr,
				tex->walls_path[i],
				&tex->walls[i]->img_width, &tex->walls[i]->img_height);
		if (!tex->walls[i]->frame)
			return (invalid_asset(mlx_ptr, tex, i, 0),
				ft_putstr_fd(TEXTURE_ERROR, 2), FALSE);
		else
			tex->walls[i]->data = (int *)mlx_get_data_addr(
					tex->walls[i]->frame, &tex->walls[i]->bpp,
					&tex->walls[i]->size_line, &tex->walls[i]->endian);
		free(tex->walls_path[i]);
		i++;
	}
	return (TRUE);
}
