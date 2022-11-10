#include "cub3d.h"

/*********** WIP *************/

static void    dda(t_map *map)
{
	
    return ;
}

void	get_values(t_map *map, int x)
{
	map->info.camera_x = 2 * x / WIDTH - 1; // width sould be DOUBLE(WIDTH) !!
	map->info.ray_x = map->info.dir_x + map->info.plane_x + map->info.camera_x;
	map->info.ray_y = map->info.dir_y + map->info.plane_y + map->info.camera_x;
    dda(map);
	return ;
}