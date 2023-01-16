#include "cub3d.h"

int	open_file(char *filepath)
{
	int	f;

	f = open(filepath, O_RDONLY);
	if (f < 0)
	{
		write(1, "Error\nFile could not be opened.\n", 33);
		exit(EXIT_FAILURE);
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
	close(f);
	return (line);
}

int	check_filetype(char *str)
{
	int	l;

	l = ft_strlen(str);
	if (str[l - 1] != 'b' || str[l - 2] != 'u'
		|| str[l - 3] != 'c' || str[l - 4] != '.')
		return (ERROR);
	return (SUCCESS);
}

/* TODO: free() content if error in parse_element */
void	parse_map(char *filepath, t_map *map)
{
	char	*content;
	int		pos;

	if (!check_filetype(filepath))
	{
		write(1, "Error\nNot .cub file.\n", 22);
		exit(0);
	}
	content = read_file(filepath);
	pos = parse_elements(map, content);
	map->map = ft_split(&content[pos], '\n');
	//printf("%s",&content[pos]);
}
