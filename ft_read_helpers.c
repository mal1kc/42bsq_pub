#include "ft.h"

t_bool	ft_write_map_data_helper(t_bsq_map_data *map_info,
		t_biggest_sq *biggest_info, char buffer_char, t_location *loc)
{
	if (loc->x >= map_info->col_len || loc->y >= map_info->line_len)
		return (false);
	if (ft_is_three_chars(map_info, buffer_char) == false)
		return (false);
	return (true);
}

t_bool	ft_save_data_helper(t_bsq_map_data *map_info,
		t_biggest_sq *biggest_info, int fd, t_location *loc)
{
	t_bool	is_first_line;
	int		read_bytes;
	char	buffer[BUFFER_SIZE];
	char	*temp;

	read_bytes = read(fd, buffer, sizeof(buffer) - 1);
	while (read_bytes > 0)
	{
		buffer[read_bytes] = '\0';
		temp = &buffer[0];
		if (is_first_line == true)
		{
			temp += map_info->map_start_index + 1;
			is_first_line = false;
		}
		if (ft_write_map_data(map_info, biggest_info, loc, temp) == false)
		{
			ft_map_data_free(map_info);
			return (false);
		}
		read_bytes = read(fd, buffer, sizeof(buffer) - 1);
	}
	return (true);
}
