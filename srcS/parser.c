/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:21:06 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 17:17:07 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	*get_textures(char **file, size_t *line)
{
	int			i;
	int			f;
	t_textures	*texts;

	*line = 0;
	texts = parse_elements(file, line);
	i = -1;
	f = 0;
	if (!texts)
		return (NULL);
	while (++i < 4)
		if (!texts->walls_path[i])
			f = 1;
	if (f || texts->ceiling == -1 || texts->floor == -1)
	{
		i = -1;
		while (++i < 4)
			if (texts->walls_path[i])
				free(texts->walls_path[i]);
		free(texts);
		return (ft_putstr_fd(ELEMENTS_ERROR, 2), NULL);
	}
	return (texts);
}

t_map	*get_map(char **file)
{
	char	**tmp_map;
	t_map	*map;

	if (!file)
		return (ft_putstr_fd(MAP_ERROR, 2), NULL);
	if (check_invalid_char(file) == ERROR)
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
	free(tmp_map);
	if (parse_map(map) == ERROR)
		return (free_2d(map->map), free(map), NULL);
	return (map);
}

t_data	*parser(char *map_path)
{
	size_t	line;
	t_data	*data;
	char	**file;

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
		return (free_2d(file), free(data->texts), free(data), NULL);
	free_2d(file);
	data->player = get_player(data->map->map);
	if (!data->player)
		return (free_2d(data->map->map), free(data->map),
			free_2d(data->texts->walls_path),
			free(data->texts), free(data), NULL);
	return (data);
}

// int	main(int ac, char **av)
// {
// 	t_data	*data;

// 	if (ac != 2)
// 	{
// 		ft_putstr_fd("Cub3D: Error: Wrong number of arguments.\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		data = parser(av[1]);
// 	if (!data)
// 		exit(EXIT_FAILURE);
// 	exit(EXIT_SUCCESS);
// }
