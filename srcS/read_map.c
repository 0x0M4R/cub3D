/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:18:57 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/03 20:10:40 by ommohame         ###   ########.fr       */
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
	if (ret <= 0)
		return (free(buff), ft_putstr_fd(FD_ERROR, 2), NULL);
/*	file = (char *)malloc(sizeof(char));
	if (!file)
		return (ft_putstr_fd(MALLOC_ERROR, 2), free(buff), NULL);
	file = "";*/
	buff[ret] = 0;
	file = ft_strdup(buff);
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = 0;
		file = ft_gnljoin(&file, buff);
	}
	free(buff);
	return (file);
}

int	check_nl(char *file)
{
	int		i;
	char	*end;
	char	*start;
	char	c;

	i = 0;
	start = file;
	while (1)
	{
		start = ft_strchr(start, '\n') + 1;
		if (start[0] == '1' || start[0] == ' ')
			break ;
	}
	while (1)
	{
		end = ft_strrchr(start, '\n') - i;
		i++;
		if (end[0] == '1' || end[0] == ' ')
			break ;
		else if (end[0] != '\n')
			return (0);
	}
	c = start[ft_strlen(start)-ft_strlen(end) + 1];
	start[ft_strlen(start)-ft_strlen(end) + 1] = 0;
	if (ft_strnstr(start, "\n\n", ft_strlen(start)))
		return (0);
	start[ft_strlen(start)-ft_strlen(end) + 1] = c;
	return (1);
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
	if (!check_nl(file))
		return (free(file), ft_putstr_fd(MAP_ERROR, 2), NULL);
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
