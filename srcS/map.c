/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:04:38 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/24 17:41:41 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				if (check_surrounding(map, i, j) == FALSE)
					return (ft_putstr_fd(MAP_ERROR, 2), FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}
