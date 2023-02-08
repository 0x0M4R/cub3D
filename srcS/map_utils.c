/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:14:17 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/05 03:57:49 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_surrounding(t_map *map, size_t i, size_t j)
{
	if (i == 0 || !ft_strchr(MAP_OBJS, map->map[i - 1][j]))
		return (FALSE);
	else if (j == 0 || !ft_strchr(MAP_OBJS, map->map[i][j - 1]))
		return (FALSE);
	else if (i == map->height - 1 || !ft_strchr(MAP_OBJS, map->map[i + 1][j]))
		return (FALSE);
	else if (j == map->width - 1 || !ft_strchr(MAP_OBJS, map->map[i][j + 1]))
		return (FALSE);
	return (TRUE);
}

int	check_invalid_char(char **file)
{
	size_t	i;
	size_t	j;
	size_t	p_count;

	i = -1;
	p_count = 0;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (!ft_strchr(MAP_CHARS, file[i][j]))
				return (ft_putstr_fd(INVALID_CHAR, 2), FALSE);
			if (ft_strchr("NSWE", file[i][j]))
				p_count++;
		}
	}
	if (p_count != 1)
		return (ft_putstr_fd(PLAYER_ERROR, 2), FALSE);
	return (TRUE);
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

char	*check_element_error(size_t elem, size_t *count)
{
	if (elem == TRUE)
		(*count)++;
	else if ((elem == FALSE && *count < 6))
		return (ft_putstr_fd(INVALID_ELEMENTS, 2), NULL);
	else if (elem == 3)
		return (ft_putstr_fd(ELEMENTS_ERROR, 2), NULL);
	return ("NO ERROR");
}
