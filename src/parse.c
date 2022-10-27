#include "../inc/cub3d.h"

/* TODO: adjust to skip lines with texture info and store somewhere else*/
void	read_map(t_map *map, int lines, char *filepath)
{
	int	f;
	int	i;

	map->map = 0;
	map->map = malloc(sizeof(char *) * (lines + 1));
	map->map[lines] = 0;
	i = 0;
	while (i < lines)
	{
		map->map[i] = 0;
		i++;
	}
	i = 0;
	f = open(filepath, O_RDONLY);
	while (i < lines)
	{
		map->map[i] = get_next_line(f);
		i++;
	}
	close(f);
}

/*TODO: only count lines of map. ie. skip lines with texture info*/
int	count_map(char *filepath, t_map *map)
{
	int		f;
	int		lines;
	int		r;
	char	buff[1];
	(void)map;
	f = open(filepath, O_RDONLY);
	if (f < 0)
	{
		write(1, "Error\nFile could not be opened.\n", 33);
		exit(0);
	}
	lines = 0;
	r = read(f, buff, 1);
	if (r < 1)
	{
		write(1, "Error\nFile could not be read.\n", 31);
		exit(0);
	}
	while (r > 0)
	{
		if (*buff == '\n')
			lines++;
		r = read(f, buff, 1);
	}
	return (lines + 1);
}
/*int	count_map(char *filepath, t_map *map)
{
	int		f;
	char	*line;
	int		r;
	char	*buff;

	f = open(filepath, O_RDONLY);
	if (f < 0)
	{
		write(1, "Error\nFile could not be opened.\n", 33);
		exit(0);
	}
	lines = 0;
	r = read(fd, buff = malloc(sizeof(char) * BUFFER_SIZE + 1), BUFFER_SIZE);
	if (r < 1)
	{
		write(1, "Error\nFile could not be read.\n", 31);
		exit(0);
	}
	while (r > 0)
	{
		buff[r] = 0;
		line = ft_gnljoin(&line, buff);
		free(buff);
		r = read(fd, buff = malloc(sizeof(char) * BUFFER_SIZE + 1), \
		BUFFER_SIZE);
	}
	return (lines + 1);
}*/
int	check_filetype(char *str)
{
	int	l;

	l = ft_strlen(str);
	if (str[l - 1] != 'b' || str[l - 2] != 'u'
		|| str[l - 3] != 'c' || str[l - 4] != '.')
		return (0);
	return (1);
}

int	parse_elements(t_map *map, char *content)
{
	(void)map;
	(void)content;
	return (0);
}

void	parse_map(char *filepath, t_map *map)
{
	int	lines;

	if (!check_filetype(filepath))
	{
		write(1, "Error\nNot .cub file.\n", 22);
		exit(0);
	}
	lines = count_map(filepath, map);
	read_map(map, lines, filepath);
}
