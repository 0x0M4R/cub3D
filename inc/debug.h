#ifndef DEBUG_H
# define DEBUG_H


#include "data.h"

t_frame tmp;

#ifndef DEBUG
# define DEBUG 0
#endif


typedef struct s_debug
{
	void	*win;
	t_dxy	ray;
	t_frame	frame;
}	t_debug;

void	draw_map(t_data data);
void	 line(t_data data, int X0, int Y0, int X1, int Y1, int color);
#endif
