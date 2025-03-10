#include "bsq.h"

void    ft_print_map(bsq_map_d *map_info, biggest_sq *bsq)
{
	int x;
	int y;
	int temp;

	y = 0;
	while (y < map_info->line_len)
	{
		x = 0;
		while (x < map_info->col_len)
		{
			temp = map_info->map_data[y][x];
			if(temp == CHAR_OBSTACLE)
				ft_putchar(map_info->obstacle);
			else if((bsq->y <= y && y <= bsq->size + bsq->y -1) && (bsq->x - bsq->size  + 1 <= x && bsq->x >= x))
			{
				ft_putchar(map_info->full);
			}
			else
				ft_putchar(map_info->space);
			x++;
		}
		
		ft_putchar('\n');
		y++;
	}
}