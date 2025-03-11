#include "ft.h"
#include <stdio.h> // test için eklendi

void	ft_print_map_info(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
{
	printf("line_len: %d\n", map_info->line_len);
	printf("col_len: %d\n", map_info->col_len);
	printf("map_start_index: %d\n", map_info->map_start_index);
	printf("file_name: %s\n", map_info->file_name);
	printf("space: %c\n", map_info->space);
	printf("obstacle: %c\n", map_info->obstacle);
	printf("full: %c\n", map_info->full);
	printf("is_stdin: %d\n", map_info->is_stdin);

	ft_print_map_data(map_info);
	ft_print_biggest(biggest_info);
}

int	ft_step_size(int nbr)
{
	int i;

	if (nbr == 0)
		return (1);
	i = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	ft_4_basamak_yazdir(int nbr)
{
	int step_size = ft_step_size(nbr);
	int i;

	i = 0;
	while (i < 4 - step_size)
	{
		printf(" ");
		i++;
	}
	printf("%d", nbr);
}

void	ft_print_map_data(t_bsq_map_data *map_info)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_info->line_len)
	{
		x = 0;
		while (x < map_info->col_len)
		{
			ft_4_basamak_yazdir(map_info->map_data[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	ft_print_biggest(t_biggest_sq *biggest_info)
{
	printf("biggest -> size: %d, x: %d, y: %d\n",biggest_info->size, biggest_info->x, biggest_info->y);
}