/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:18:57 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/05 05:07:59 by ommohame         ###   ########.fr       */
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

int	find_end(char *start)
{
	size_t	i;
	char	*end;

	i = 0;
	if ((start)[ft_strlen(start) - 1] == '1' ||
		(start)[ft_strlen(start) - 1] == ' ')
		return (1);
	while (1)
	{
		end = ft_strdup(ft_strrchr(start, '\n') - i);
		i++;
		if (!(end))
			return (0);
		if (end[0] == '1' || end[0] == ' ')
			break ;
		else if (end[0] != '\n')
			return (free(end), 0);
		free(end);
	}
	free(end);
	return (ft_strlen(end));
}

int	check_nl(char *file)
{
	int		f;
	size_t	i;

	i = 0;
	f = FALSE;
	while (f == FALSE && file[i])
	{
		if (i != 0 && file[i] && file[i - 1] == '\n' \
						&& ft_strchr(" 1", file[i]))
			f = TRUE;
		i++;
	}
	while (file[i])
	{
		if (i != 0 && file[i] && file[i - 1] == '\n' && file[i] == '\n')
			break ;
		i++;
	}
	while (file[i])
	{
		if (file[i] != '\0' && file[i] != '\n')
			f = FALSE;
		i++;
	}
	return (f);
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
	if (check_nl(file) == FALSE)
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
