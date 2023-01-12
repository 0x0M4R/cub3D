#include "cub3d.h"

/* TODO : check errors in color.
		- must be between 0-255
		- last color must be followed by only /n
		- must have 3 colors  */
t_rgb	get_element_rgb(char *element, int len)
{
	t_rgb	color;
	char	**str_color;

	str_color = ft_split(ft_strrchr(ft_substr(element, 0, len), ' '), ',');
	color.red = ft_atoi(str_color[0]);
	color.green = ft_atoi(str_color[1]);
	color.blue = ft_atoi(str_color[2]);
	//free 2d array.
	return (color);
}

/* TODO: check for errors in path 
	- must end in newline
	- must be valid path  */
char	*get_element(char *element, int len)
{
	//printf("%s", ft_strrchr(ft_substr(element, 0, len), ' '));
	return (ft_strdup(ft_strrchr(ft_substr(element, 0, len), ' ') + 1));
}

int	match_element(t_map *map, char *element)
{
	int	len;

	len = ft_strlen(element) - ft_strlen(ft_strchr(element, '\n'));
	if (!ft_strncmp(element, "NO ", 3))
		map->tex[0].path = get_element(element, len);
	else if (!ft_strncmp(element, "SO ", 3))
		map->tex[1].path = get_element(element, len);
	else if (!ft_strncmp(element, "WE ", 3))
		map->tex[2].path = get_element(element, len);
	else if (!ft_strncmp(element, "EA ", 3))
		map->tex[3].path = get_element(element, len);
	else if (!ft_strncmp(element, "F ", 2))
		map->floor = get_element_rgb(element, len);
	else if (!ft_strncmp(element, "C ", 2))
		map->ceiling = get_element_rgb(element, len);
	else
	{
		write(1, "Error\nMissing element information .\n", 22);
		exit(0);
	}
	return (len);
}

int	parse_elements(t_map *map, char *content)
{
	int	i;
	int	e_count;
	int	pos;

	(void)map;
	(void)content;
	i = 0;
	e_count = 0;
	pos = 0;
	while (content[i])
	{
		if ((i == 0 || (content[i] != '\n' && i != 0)) && e_count < 6)
		{
			i += match_element(map, &content[i]) + 1;
			e_count++;
			if (e_count == 6)
				pos = i;
		}
		else
			i++;
	}
	if (ft_strchr_i(&content[pos], '1') > ft_strchr_i(&content[pos], ' '))
		return (pos + ft_strchr_i(&content[pos], ' '));
	else
		return (pos + ft_strchr_i(&content[pos], '1'));
}
