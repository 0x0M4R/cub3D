void	draw_square(t_map map, int x1, int y1)
{
	int		x2;
	int		y2;

	y2 = y1;
	while (y2 < y1 + 100 && y2 < HEIGHT)
	{
		x2 = x1;
		while (x2 < x1 + 100 && x2 < WIDTH)
		{
			mlx_pixel_put(map.mlx.mlx, map.mlx.win, x2, y2, 0x88CDF6);
			x2++;
		}
		y2++;
	}
}
