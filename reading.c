#include "bsq.h"

int	ft_check_first_line(bsq_map_d *map_info, char *first_line)
{
	/* Kontrol edilmesi gerekenler:
	--- karakter eksikse
	--- iki karakter birbiriyle aynıysa
	--- sıkıntı yoksa map_info içerisine bilgiler yazılmalı
	*/

	int	i;
	int	j;
	int line_len;

	line_len = 0;
	while (*first_line >= '0' && *first_line <= '9')
	{
		line_len *= 10;
		line_len += *first_line - '0';
		first_line++;
	}
	if (line_len <= 0)
		return (0);

	i = 0;
	while (first_line[i])
	{
		j = 0;
		while (first_line[j])
		{
			if (first_line[i] == first_line[j] && i != j)
				return (0);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (0);

	map_info->line_len = line_len;
	map_info->space = first_line[0];
	map_info->obstacle = first_line[1];
	map_info->full = first_line[2];

	return (1);
}

t_bool	ft_read_map(bsq_map_d *map_info, int fd)
{
	/* Yapılması gerekenler:
	--- map_info içindeki map_data içerisine malloc ile dizileri oluşturup 
	bilgileri içerisine girmek gerekiyor
	--- karakterleri .ox formatına çeviyor
	--- satır ve kolon uzunluğunu kontrol ediyor
	--- istenmeyen bir karakter var mı kontrol ediyor
	*/

	char buffer[MAP_READ_BUFF_SIZE];
	int rb;
	int i;
	int line_len;
	int col_len;
	t_bool is_map_started;
	int	sq_counter;

	map_info->map_data = (int**)malloc(sizeof(int*) * map_info->line_len);
	if (map_info == NULL)
		exit(1);
	i = 0;
	while (i< map_info->line_len)
	{
		map_info->map_data[i] = (int*)malloc(sizeof(int) * (map_info->col_len));
		if (map_info->map_data[i] == NULL)
			exit(1);
		i++;
	}

	is_map_started = false;
	line_len = 0;
	col_len = 0;
	sq_counter = 1;
	while (1)
	{
		rb = read(fd, buffer, sizeof(buffer) - 1);
		if (rb <= 0)
			break;
		buffer[rb] = '\0';

				i = 0;
		while (buffer[i])
		{
			if (is_map_started == false && map_info->map_start_index + 1 == i)
				is_map_started  = true;

			if (is_map_started == true)
			{
				if (buffer[i] == '\n')
				{
					line_len++;
					col_len = 0;
					sq_counter = 1;
					i++;
					continue;
				}

				if (buffer[i] != map_info->full && buffer[i] != map_info->obstacle && buffer[i] != map_info->space)
					return (false);
				// if (buffer[i] == map_info->full)
				// 	return (false);

				if (col_len > map_info->col_len)
					return (false);
				if (line_len > map_info->line_len)
					return (false);
				
				if (buffer[i] == map_info->obstacle)
				{
					map_info->map_data[line_len][col_len] = CHAR_OBSTACLE;
					sq_counter = 1;
					col_len++;
					i++;
					continue ;
				}
				else if (buffer[i] == map_info->space)
					map_info->map_data[line_len][col_len] = sq_counter;

				sq_counter++;
				col_len++;
			}
			i++;
		}
	}

	return (true);
}

t_bool ft_check_map_chars(char full, char obstacle, char space)
{
	if (full == obstacle || full == space || space == obstacle)
		return (false);
	
	if (!(full >= 32 && full <= 126))
		return (false);
	if (!(obstacle >= 32 && obstacle <= 126))
		return (false);
	if (!(space >= 32 && space <= 126))
		return (false);
	
	return (true);
}

t_bool ft_read_first_line(bsq_map_d *map_info, char* buffer)
{
	int i;
	int map_line_len;

	if (map_info->map_start_index < MIN_LEN_FLINE)
		return (false);

	i = map_info->map_start_index - 1;
	map_info->full = buffer[i--];
	map_info->obstacle = buffer[i--];
	map_info->space = buffer[i--];

	if (ft_check_map_chars(map_info->full, map_info->obstacle, map_info->space) == false)
		return (false);

	// 1234.ox
	//    ^
	//    i
	map_info->line_len = 0;
	map_line_len = 1;
	while (i >= 0)
	{
		if (!(buffer[i] >= '0' && buffer[i] <= '9'))
			return (false);
		map_info->line_len += map_line_len * (buffer[i--] - '0');
		map_line_len *= 10;
	}

	return (true);
}

t_bool	ft_col_count_calculate(bsq_map_d *map_info ,char *file_name, int is_stdin)
{
	/*
	ilk satır okunacak
	map_start_index belirlenecek
	kolon sayısı bulunacak
	*/
	int	fd;
	char buffer[100];
	int rb;
	int rbi;
	t_bool is_first;
	t_bool r_finish;

	if (is_stdin)
	{
		fd = STDIN_FILENO;
	} else 
	{
		fd = open(file_name, O_RDONLY);
		if (fd == -1)
			return (false);
	}

	rb = 0;
	rbi = 0;
	r_finish = false;
	is_first = true;
	map_info->map_start_index = 0;
	map_info->col_len = 0;
	while (!r_finish)
	{
		rb = read(fd, buffer, sizeof(buffer) - 1);
		if (rb <= 0)
			break;
		buffer[rb] = '\0';
		while (buffer[rbi])
		{
			if (is_first == true && buffer[rbi] != '\n')
				map_info->map_start_index++;
			if (is_first == false && buffer[rbi] != '\n')
				map_info->col_len++;
			if (is_first == false && buffer[rbi] == '\n')
			{
				r_finish = true;
				break;
			}
			if (buffer[rbi] == '\n' && is_first == true)
			{
				if (ft_read_first_line(map_info, buffer) == false)
					return (false);
				is_first = false;
			}
			rbi++;
		}
	}

	if (map_info->col_len <= 0)
		return (false);
	
	close(fd);
	return (true);
}
