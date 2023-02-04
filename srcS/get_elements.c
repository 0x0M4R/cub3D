/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:36:26 by ommohame          #+#    #+#             */
/*   Updated: 2023/02/04 20:39:10 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_element(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (NORTH);
	else if (!ft_strncmp(line, "SO ", 3))
		return (SOUTH);
	else if (!ft_strncmp(line, "WE ", 3))
		return (WEST);
	else if (!ft_strncmp(line, "EA ", 3))
		return (EAST);
	else if (!ft_strncmp(line, "F ", 2))
		return (FLOOR);
	else if (!ft_strncmp(line, "C ", 2))
		return (CEILING);
	else
		return (FALSE);
}

static int	get_color(char *color_str)
{
	size_t	i;
	int		color;
	char	*trim;

	i = -1;
	if (!color_str)
		return (-1);
	trim = ft_strtrim(color_str, " ");
	while (trim[++i])
		if (!ft_isdigit(trim[i]))
			return (free(trim), -1);
	free(trim);
	color = ft_atoi(color_str);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

static int	get_colors(char *line)
{
	int		count;
	size_t	i;
	t_rgb	rgb;
	char	**colors;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			count++;
		if (count > 2)
			return (ft_putstr_fd(COLOR_ERROR, 2), -1);
	}
	colors = ft_split(line, ',');
	if (!colors)
		return (ft_putstr_fd(MALLOC_ERROR, 2), -1);
	if (ft_strlenx2(colors) != 3)
		return (ft_putstr_fd(COLOR_ERROR, 2), -1);
	rgb.red = get_color(colors[0]);
	rgb.green = get_color(colors[1]);
	rgb.blue = get_color(colors[2]);
	if (rgb.red == -1 || rgb.green == -1 || rgb.blue == -1)
		return (ft_putstr_fd(COLOR_ERROR, 2), -1);
	return (rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

static int	get_element(t_textures *text, char *line, int element)
{
	if (element == FALSE)
		return (FALSE);
	if (element >= NORTH && element <= EAST)
	{
		if (text->walls_path[element - 1])
			return (3);
		text->walls_path[element - 1] = ft_strtrim(line + 3, " ");
		return (TRUE);
	}
	else if (element == FLOOR)
		return (text->floor = get_colors(line + 2), TRUE);
	else if (element == CEILING)
		return (text->ceiling = get_colors(line + 2), TRUE);
	return (FALSE);
}

t_textures	*parse_elements(char **file, size_t *line)
{
	size_t		i;
	size_t		count;
	t_textures	*text;

	i = -1;
	count = 0;
	text = (t_textures *)malloc(sizeof(t_textures));
	if (!text)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	text->floor = -1;
	text->ceiling = -1;
	while (++i < 4)
		text->walls_path[i] = NULL;
	i = -1;
	while (file[++i])
	{
		if (!check_element_error(get_element(text, file[i],
					check_element(file[i])), &count))
			return (NULL);
		if (count == 6 && *line == 0)
			*line = i + 1;
	}
	if (count != 6)
		return (ft_putstr_fd(ELEMENTS_ERROR, 2), NULL);
	return (text);
}
