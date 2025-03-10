#include "bsq.h"

t_bool	check_below(bsq_map_d *map_info,  biggest_sq *bsq, biggest_sq *check_sq)
{
	int i;
	int temp;
	int x;
	int y;
	int possible_size;

	possible_size = 1;
	i = 0;
	x = check_sq->x;
	y = check_sq->y;
	while (i < check_sq->size - 1)
	{
		y++;
		if (y >= map_info->line_len)
			return (false);
		temp = map_info->map_data[y][x];
		if (temp < check_sq->size )
		{
			check_sq->size = temp;
		}
		possible_size++;
		if (check_sq->size == possible_size)
		{
			if (check_sq->size > bsq->size)
				return (true);
		}
		i++;
	}

	return (false);
}

void	process_map(bsq_map_d *map_info, biggest_sq *bsq)
{
	int x;
	int y;
	int temp;
	biggest_sq temp_sq;

	y = 0;
	while (y < map_info->line_len)
	{
		x = 0;
		while (x < map_info->col_len)
		{
			temp = map_info->map_data[y][x];
			if (temp == -2 || temp <= bsq->size)
			{
				x++;
				continue;
			}

			temp_sq.size = temp;
			temp_sq.x = x;
			temp_sq.y = y;
			if (check_below(map_info, bsq, &temp_sq)){
				bsq->size = temp_sq.size;
				bsq->x = temp_sq.x;
				bsq->y = temp_sq.y;
				// ft_print_bsq(bsq);
			}

			x++;
		}
		y++;
	}
	
}