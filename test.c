// // #include <math.h>
// // #include <stdlib.h>
// // #include <stdio.h>

// // typedef struct s_ixy
// // {
// // 	int		x;
// // 	int		y;
// // }	t_ixy;

// // typedef struct s_algo
// // {
// // 	int		dx;
// // 	int		dy;
// // 	t_ixy	p1;
// // 	t_ixy	p2;
// // }	t_algo;

// // void	plot_pixel(t_algo *test, int decide)
// // {
// // 	int		i;
// // 	int		pk;

// // 	i = 0;
// // 	pk = 2 * test->dy - test->dx;
// // 	while (i <= test->dx)
// // 	{
// // 		printf("%d, %d\n", test->p1.x, test->p1.y);
// // 		if (test->p1.x < test->p2.x)
// // 			test->p1.x++;
// // 		else
// // 			test->p1.x--;
// // 		if (pk < 0)
// // 			pk = pk + 2 * test->dy;
// // 		else
// // 		{
// // 			if (test->p1.y < test->p2.y)
// // 				test->p1.y++;
// // 			else
// // 				test->p1.y--;
// // 			pk = pk + 2 * test->dy - 2 * test->dx;
// // 		}
// // 		i++;
// // 	}
// // }

// // void	bresenham_algo(t_algo *test)
// // {
// // 	test->dx = abs(test->p2.x - test->p1.x);
// // 	test->dy = abs(test->p2.y - test->p1.y);
// // 	if (test->dx > test->dy)
// // 		plot_pixel(test, 0);
// // 	else
// // 		plot_pixel(test, 1);
// // }

// // int	main(void)
// // {
// // 	t_algo	test;

// // 	test.p1.x = -2;
// // 	test.p1.y = -4;
// // 	test.p2.x = 2;
// // 	test.p2.y = 4;
// // 	bresenham_algo(&test);
// // 	return (0);
// // }
// // C program for DDA line generation

// // #include <graphics.h>
// #include <math.h>
// #include <stdio.h>
// // Function for finding absolute value
// int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

// // DDA Function for line generation
// void DDA(int X0, int Y0, int X1, int Y1)
// {
// 	// calculate dx & dy
// 	int dx = X1 - X0;
// 	int dy = Y1 - Y0;

// 	// calculate steps required for generating pixels
// 	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

// 	// calculate increment in x & y for each steps
// 	float Xinc = dx / (float)steps;
// 	float Yinc = dy / (float)steps;

// 	// Put pixel for each step
// 	float X = X0;
// 	float Y = Y0;
// 	for (int i = 0; i <= steps; i++) {
// 		// putpixel(round(X), round(Y),
// 				// RED); // put pixel at (X,Y)
// 		X += Xinc; // increment in x at each step
// 		Y += Yinc; // increment in y at each step
// 		// delay(100); // for visualization of line-
// 					// generation step by step
// 		printf("%f, %f\n", X, Y);
// 	}
// }

// // Driver program
// int main()
// {
// 	// int gd = DETECT, gm;

// 	// Initialize graphics function
// 	// initgraph(&gd, &gm, "");

// 	int X0 = -2, Y0 = -4, X1 = 2, Y1 = 4;

// 	// Function call
// 	DDA(2, 2, 14, 16);
// 	return 0;
// }
#include <stdio.h>
# define T 1
int main()
{
	printf("%d, %d\n", T, -T);
}