/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:26:25 by ommohame          #+#    #+#             */
/*   Updated: 2023/01/29 16:09:52 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double deg)
{
	return (deg * M_PI / (double)180);
}

double	get_dst(t_dxy p1, t_dxy p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

double	fix_angle(double angle)
{
	if (angle < 0)
		return (angle + 360.0);
	else if (angle > 360.0)
		return (angle - 360.0);
	else
		return (angle);
}

void	free_2d(char **str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

size_t	ft_strlenx2(char **str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
