/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:21:06 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/20 00:26:46 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*parser(char *map_path)
{
	size_t	line;
	t_data	*data;
	char	**file;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
	file = get_file(map_path);
	if (!file)
		return (free(data), NULL);
	data->texts = get_textures(file, &line);
	if (!data->texts)
		return (free_2d(file), free(data), NULL);
	data->map = get_map(file + line);
	if (!data->map)
		return (free_2d(file), free(data->texts), free(data), NULL);
	free_2d(file);
	return (data);
}

// int	main(int ac, char **av)
// {
// 	t_data	*data;

// 	if (ac != 2)
// 	{
// 		ft_putstr_fd("Cub3D: Error: Wrong number of arguments.\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		data = parser(av[1]);
// 	if (!data)
// 		exit(EXIT_FAILURE);
// 	exit(EXIT_SUCCESS);
// }
