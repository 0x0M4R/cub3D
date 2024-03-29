/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:21:06 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/08 19:57:08 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_filetype(char *str)
{
	int	l;

	l = ft_strlen(str);
	if (str[l - 1] != 'b' || str[l - 2] != 'u'
		|| str[l - 3] != 'c' || str[l - 4] != '.')
		return (0);
	return (1);
}

void	free_textures_path(t_textures *texts)
{
	int			i;

	i = -1;
	while (++i < 4)
		if (texts->walls_path[i])
			free(texts->walls_path[i]);
	free(texts);
}

t_textures	*get_textures(char **file, size_t *line)
{
	int			i;
	int			f;
	t_textures	*texts;

	*line = 0;
	texts = parse_elements(file, line);
	if (!texts)
		return (NULL);
	i = -1;
	f = 0;
	while (++i < 4)
		if (!texts->walls_path[i])
			f = 1;
	if (f || texts->ceiling == -1 || texts->floor == -1)
	{
		free_textures_path(texts);
		return (NULL);
	}
	return (texts);
}

t_map	*get_map(char **file)
{
	char	**tmp_map;
	t_map	*map;

	if (!file)
		return (ft_putstr_fd(MAP_ERROR, 2), NULL);
	if (check_invalid_char(file) == FALSE)
		return (NULL);
	tmp_map = trim_map(file);
	if (!tmp_map)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (free_2d(tmp_map), ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	map->width = get_width(tmp_map);
	map->height = ft_strlenx2(tmp_map);
	map->map = squareazz(tmp_map, map->width, map->height);
	free_2d(tmp_map);
	if (parse_map(map) == FALSE)
		return (free_2d(map->map), free(map), NULL);
	return (map);
}

int	load_assets(void *mlx_ptr, t_textures *tex)
{
	int		ret;

	ret = TRUE;
	if (load_gun(mlx_ptr, tex) == FALSE)
		ret = FALSE;
	if (ret == TRUE && load_walls(mlx_ptr, tex) == FALSE)
		ret = FALSE;
	if (ret == TRUE && load_door(mlx_ptr, tex) == FALSE)
	{
		ret = FALSE;
		invalid_asset(mlx_ptr, tex, 5, 0);
	}
	if (ret == FALSE)
		free(tex);
	return (ret);
}

t_data	*parser(char *map_path)
{
	size_t	line;
	t_data	*data;
	char	**file;

	if (!check_filetype(map_path))
		return (ft_putstr_fd(EXTENSION_ERROR, 2), NULL);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	file = get_file(map_path);
	if (!file)
		return (free(data), NULL);
	data->texts = get_textures(file, &line);
	if (!data->texts)
		return (free_2d(file), free(data), NULL);
	data->map = get_map(file + line);
	if (!data->map)
		return (free_2d(file), free_textures_path(data->texts),
			free(data), NULL);
	free_2d(file);
	data->player = get_player(data->map->map);
	if (!data->player)
		return (free_2d(data->map->map), free(data->map),
			free_textures_path(data->texts),
			free(data->texts), free(data), NULL);
	return (data);
}
