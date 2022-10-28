#include "../inc/cub3d.h"

/* TODO: adjust to skip lines with texture info */
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

int	open_file(char *filepath)
{
	int	f;

	f = open(filepath, O_RDONLY);
	if (f < 0)
	{
		write(1, "Error\nFile could not be opened.\n", 33);
		exit(0);
	}
	return (f);
}

char	*read_file(char *filepath)
{
	char	*line;
	int		r;
	char	*buff;
	int		f;

	f = open_file(filepath);
	r = read(f, buff = malloc(sizeof(char) * BUFFER_SIZE + 1), BUFFER_SIZE);
	if (r < 1)
	{
		write(1, "Error\nFile could not be read.\n", 31);
		exit(0);
	}
	line = malloc(sizeof(char));
	line = "";
	while (r > 0)
	{
		buff[r] = 0;
		line = ft_gnljoin(&line, buff);
		free(buff);
		r = read(f, buff = malloc(sizeof(char) * BUFFER_SIZE + 1), \
		BUFFER_SIZE);
	}
	return (line);
}

int	check_filetype(char *str)
{
	int	l;

	l = ft_strlen(str);
	if (str[l - 1] != 'b' || str[l - 2] != 'u'
		|| str[l - 3] != 'c' || str[l - 4] != '.')
		return (0);
	return (1);
}

void	parse_map(char *filepath, t_map *map)
{
	char	*content;
	int		line_num;

	if (!check_filetype(filepath))
	{
		write(1, "Error\nNot .cub file.\n", 22);
		exit(0);
	}
	content = read_file(filepath);
	line_num = parse_elements(map, content);
	printf("hello%s",map->w_texture);
	read_map(map, 15, filepath);
}
