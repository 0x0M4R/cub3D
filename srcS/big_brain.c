/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:12:55 by ommohame          #+#    #+#             */
/*   Updated: 2022/11/13 18:16:51 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********** WIP *************/


static void	init_values(t_player *player, int x)
{
	player->camera_x = 2 * x / (double)WIDTH - 1;
	player->render.ray.x = player->dir.x + player->render.plane.x * player->camera_x;
	player->render.ray.y = player->dir.y + player->render.plane.y * player->camera_x;
	player->map.x = (int)player->pos.x;
	player->map.y = (int)player->pos.y;
}

static void get_delta(t_player *player)
{
	if (!player->render.ray.x)
		player->render.delta.x = 1e30;
	else
		player->render.delta.x = fabs(1 / player->render.ray.x);
	if (!player->render.ray.y)
		player->render.delta.y = 1e30;
	else
		player->render.delta.y = fabs(1 / player->render.ray.y);
}

static void	calculate_step(t_player *player)
{
	if (player->render.ray.x < 0)
	{
		player->render.step.x = -1;
		player->render.dst.x = (player->pos.x - player->map.x) * player->render.delta.x;
	}
	else
	{
		player->render.step.x = 1;
		player->render.dst.x = (player->map.x + 1.0 - player->pos.x) * player->render.delta.x;
	}
	if (player->render.ray.y < 0)
	{
		player->render.step.y = -1;
		player->render.dst.y = (player->pos.y - player->map.y) * player->render.delta.y;
	}
	else
	{
		player->render.step.y = 1;
		player->render.dst.y = (player->map.y + 1.0 - player->pos.y) * player->render.delta.y;
	}
}

static void	dda(t_map *map)
{
	int		hit;

	hit = 0;
	get_delta(&map->player);
	calculate_step(&map->player);
	while (!hit)
	{
		if (map->player.render.dst.x < map->player.render.dst.y)
		{
			map->player.render.dst.x += map->player.render.delta.x;
			map->player.map.x += map->player.render.step.x;
			map->player.side = 0;
		}
		else
		{
			map->player.render.dst.y += map->player.render.delta.y;
			map->player.map.y += map->player.render.step.y;
			map->player.side = 1;
		}
		if (map->map[map->player.map.x][map->player.map.y] == '1')
			hit = 1;
	}
}

static void	line_height (t_player *player)
{
	int		height;
	double	wall_dis;

	if (!player->side)
		wall_dis = player->render.dst.x - player->render.delta.x;
	else
		wall_dis = player->render.dst.y - player->render.delta.y;
	height = (int)(HEIGHT / wall_dis);
	player->render.draw.x = -height / 2 + HEIGHT / 2;
	if (player->render.draw.x < 0)
		player->render.draw.x = 0;
	player->render.draw.y = height / 2 + HEIGHT / 2;
	if (player->render.draw.y >= HEIGHT)
		player->render.draw.y = HEIGHT - 1;
}

static void get_color(t_map *map)
{
	map->player.render.color = RED;
	if (map->player.side == 1)
		map->player.render.color /= 2;
}

void	get_values(t_map *map, int x)
{
	init_values(&map->player, x);
	dda(map);
	line_height(&map->player);
	get_color(map);
	return ;
}
