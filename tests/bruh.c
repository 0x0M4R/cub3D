int	test(t_map *map)
{
	int		x;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dst_x;
	double	side_dst_y;
	double	delta_dst_x;
	double	delta_dst_y;
	double	perp_wall_dst;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;

	x = 0;
	pos_x = 22;
	pos_y = 12;
	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir_x = dir_x + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_x;
		map_x = pos_x;
		map_y = pos_y;
		if (ray_dir_x == 0)
			delta_dst_x = 1e30;
		else
			delta_dst_x = abs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dst_y = 1e30;
		else
			delta_dst_y = abs(1 / ray_dir_y);
		hit = 0;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dst_x = (pos_x - map_x) * delta_dst_x;
		}
		else
		{
			step_x = 1;
			side_dst_x = (pos_x + 1.0 - map_x) * delta_dst_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dst_y = (pos_y - map_y) * delta_dst_y;
		}
		else
		{
			step_y = 1;
			side_dst_y = (pos_y + 1.0 - map_y) * delta_dst_y;
		}
		while (hit == 0)
		{
			if (side_dst_x < side_dst_y)
			{
				side_dst_x += delta_dst_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dst_y += delta_dst_y;
				map_y += step_y;
				side = 1;
			}
			if (map->map[map_x][map_y] != '0')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dst = (side_dst_x - delta_dst_x);
		else
			perp_wall_dst = (side_dst_y - delta_dst_y);
		line_height = (int)(HEIGHT / perp_wall_dst);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		while (draw_start <= draw_end)
		{
			mlx_pixel_put(map->mlx.mlx, map->mlx.win, x, draw_start, 0x88CDF6);
			draw_start++;
		}
		x++;
	}
	return (SUCCESS);
}