#include "ft.h"

t_bool	ft_map_data_malloc(t_bsq_map_data *map_info)
{
	int	y;

	map_info->map_data = (int **)malloc(sizeof(int *) * map_info->line_len);
	if (map_info->map_data == NULL)
		exit(EXIT_FAILURE);
	y = 0;
	while (y < map_info->line_len)
	{
		map_info->map_data[y] = (int *)malloc(sizeof(int) * map_info->col_len);
		if (map_info->map_data[y] == NULL)
		{
			while (--y >= 0)
				free(map_info->map_data[y]);
			free(map_info->map_data);
			map_info->map_data = NULL;
			exit(EXIT_FAILURE);
		}
		y++;
	}
	return (true);
}

char	*ft_line_temp_malloc(t_bsq_map_data *map_info,
		t_biggest_sq *biggest_info)
{
	char	*line_temp;

	line_temp = (char *)malloc(sizeof(char) * (map_info->col_len + 1));
	if (line_temp == NULL)
		ft_print_sol2(map_info, biggest_info);
	return (line_temp);
}
