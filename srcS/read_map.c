/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:18:57 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/25 11:32:21 by ommohame         ###   ########.fr       */
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
	file = (char *)malloc(sizeof(char));
	if (!file)
		return (ft_putstr_fd(MALLOC_ERROR, 2), free(buff), NULL);
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
