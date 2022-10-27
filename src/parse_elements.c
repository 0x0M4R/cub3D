#include "../inc/cub3d.h"

/*TODO!!*/
t_rgb	get_element_rgb(char *element, int len)
{
	t_rgb	color;

	(void)len;
	color.red = 0;
	color.blue = 0;
	color.green = 0;
	printf("%s\n", element);
	return (color);
}

char	*get_element(char *element, int len)
{
	return (ft_strrchr(ft_substr(element, 0, len), ' '));
}

int	match_element(t_map *map, char *element)
{
	int	len;

	len = ft_strlen(element) - ft_strlen(ft_strchr(element, '\n'));
	if (ft_strncmp(element, "NO ", 3))
		map->n_texture = get_element(element, len);
	else if (ft_strncmp(element, "SO ", 3))
		map->s_texture = get_element(element, len);
	else if (ft_strncmp(element, "WE ", 3))
		map->w_texture = get_element(element, len);
	else if (ft_strncmp(element, "EA ", 3))
		map->e_texture = get_element(element, len);
	else if (ft_strncmp(element, "F ", 2))
		map->floor = get_element_rgb(element, len);
	else if (ft_strncmp(element, "C ", 2))
		map->ceiling = get_element_rgb(element, len);
	else
	{
		write(1, "Error\nNot .cub file.\n", 22);
		exit(0);
	}
	return (len);
}

/* TODO: count how many lines and return to feed read_map function */
int	parse_elements(t_map *map, char *content)
{
	int	i;
	int	e_count;

	(void)map;
	(void)content;
	i = 0;
	e_count = 0;
	while (content[i])
	{
		if ((i == 0 || (content[i] != '\n' && i != 0)) && e_count < 6)
		{
			i += match_element(map, &content[i]) + 1;
			e_count++;
		}
		else
			i++;
	}
	return (0);
}
