/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:04:38 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/19 23:57:09 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_file(int fd)
{
	int		ret;
	char	*buff;
	char	*file;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	ret = read(fd, buff, BUFFER_SIZE);
	if (ret < 0)
		return (ft_putstr_fd(FD_ERROR, 2), NULL);
	file = (char *)malloc(sizeof(char));
	file = "";
	while (ret > 0)
	{
		buff[ret] = 0;
		file = ft_gnljoin(&file, buff);
		ret = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (file);
}

static char	**read_map_file(char *map_path)
{
	int		fd;
	char	*file;
	char	**split_file;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(FD_ERROR, 2), NULL);
	file = read_file(fd);
	close(fd);
	if (!file)
		return (NULL);
	split_file = ft_split(file, '\n');
	free(file);
	if (!split_file)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	return (split_file);
}

char	**get_file(char *map_path)
{
	char	**file;

	file = read_map_file(map_path);
	if (!file)
		return (NULL);
	return (file);
}

size_t	get_start(char **file)
{
	size_t	start;
	size_t	file_len;
	char	*trim;

	start = 0;
	file_len = ft_strlenx2(file);
	while (start < file_len)
	{
		trim = ft_strtrim(file[start], " \n");
		if (trim != NULL)
		{
			free(trim);
			break ;
		}
		start++;
	}
	return (start);
}

size_t	get_end(char **file, size_t start)
{
	size_t	end;
	char	*trim;

	end = ft_strlenx2(file) - 1;
	while (end > start)
	{
		trim = ft_strtrim(file[end], " \n");
		if (trim != NULL)
		{
			free(trim);
			break ;
		}
		end--;
	}
	return (end);
}

char	**trim_map(char **file)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	**map;

	start = get_start(file);
	end = get_end(file, start);
	if (start == end)
		return (ft_putstr_fd(MAP_ERROR, 2), NULL);
	map = (char **)malloc(sizeof(char *) * (end - start + 2));
	if (!map)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	i = -1;
	while (++i <= end)
		map[i] = ft_strdup(file[i + start]);
	map[i] = NULL;
	return (map);
}

size_t	get_width(char **map)
{
	size_t	i;
	size_t	len;
	size_t	tmp;

	i = 0;
	len = 0;
	while (map[i])
	{
		tmp = ft_strlen(map[i]);
		if (tmp > len)
			len = tmp;
		i++;
	}
	return (len);
}

char	**squareazz(char **tmp_map, size_t width, size_t height)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	while (i < height)
	{
		map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!map[i])
			return (free_2d(map), ft_putstr_fd(MALLOC_ERROR, 2), NULL);
		j = 0;
		while (j < width)
		{
			if (j < ft_strlen(tmp_map[i]))
				map[i][j] = tmp_map[i][j];
			else
				map[i][j] = ' ';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	check_invalid_char(char **file)
{
	size_t	i;
	size_t	j;
	size_t	p_count;
	char	*trim;

	i = -1;
	p_count = 0;
	while (file[++i])
	{
		j = -1;
		trim = ft_strtrim(file[i], " ");
		if (!trim || !*trim)
			return (free(trim), ft_putstr_fd(INVALID_CHAR, 2), ERROR);
		free(trim);
		while (file[i][++j])
		{
			if (!ft_strchr(MAP_CHARS, file[i][j]))
				return (ft_putstr_fd(INVALID_CHAR, 2), ERROR);
			if (ft_strchr("NSWE", file[i][j]))
				p_count++;
		}
	}
	if (p_count != 1)
		return (ft_putstr_fd(PLAYER_ERROR, 2), ERROR);
	return (SUCCESS);
}

int	check_surrounding(t_map *map, size_t i, size_t j)
{
	if (i == 0 || !ft_strchr(MAP_OBJS, map->map[i - 1][j]))
		return (ERROR);
	else if (j == 0 || !ft_strchr(MAP_OBJS, map->map[i][j - 1]))
		return (ERROR);
	else if (i == map->height - 1 || !ft_strchr(MAP_OBJS, map->map[i + 1][j]))
		return (ERROR);
	else if (j == map->width - 1 || !ft_strchr(MAP_OBJS, map->map[i][j + 1]))
		return (ERROR);
	return (SUCCESS);
}

int	parse_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '0')
			{
				if (check_surrounding(map, i, j) == ERROR)
					return (ft_putstr_fd(MAP_ERROR, 2), ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
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
