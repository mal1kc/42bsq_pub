#include "bsq.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void ft_reset_mapData(bsq_map_d *map_info)
{
	int i;

	if (map_info->map_data != NULL)
	{
		i = 0;
		while (i < map_info->line_len)
			free(map_info->map_data[i++]);
		free(map_info->map_data);
		map_info->map_data = NULL;		
	}
	
	map_info->line_len = -1;
	map_info->col_len = -1;
	map_info->map_start_index = -1;
	map_info->file_name = "";
	map_info->space = '\0';
	map_info->obstacle = '\0';
	map_info->full = '\0';
	map_info->map_data = NULL;		
}

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

void	ft_print_map(bsq_map_d *map_info)
{
	int i;
	int j;

	i = 0;
	while (i < map_info->line_len)
	{
		j = 0;
		while (j < map_info->col_len)
			write(1, &map_info->map_data[i][j++], 1);
		write(1, "\n", 1);
		i++;
	}
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

	map_info->map_data = (char**)malloc(sizeof(char*) * map_info->line_len);
	if (map_info == NULL)
		exit(1);
	i = 0;
	while (i< map_info->line_len)
	{
		map_info->map_data[i] = (char*)malloc(sizeof(char) * (map_info->col_len + 1));
		if (map_info->map_data[i] == NULL)
			exit(1);
		i++;
	}

	is_map_started = false;
	line_len = 0;
	col_len = 0;
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
					i++;
					continue;
				}

				if (buffer[i] != map_info->full && buffer[i] != map_info->obstacle && buffer[i] != map_info->space)
					return (false);

				if (col_len > map_info->col_len)
					return (false);
				if (line_len > map_info->line_len)
					return (false);

				if (buffer[i] == map_info->obstacle)
					map_info->map_data[line_len][col_len] = CHAR_OBSTACLE;
				else if (buffer[i] == map_info->full)
					map_info->map_data[line_len][col_len] = CHAR_FULL;
				else if (buffer[i] == map_info->space)
					map_info->map_data[line_len][col_len] = CHAR_SPACE;

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

int	main(int argc, char **argv)
{
	bsq_map_d map_info;
	int	fd;
	int i;
	t_bool return_status;

	/*
	test0: col=7, line=7
	test1: col=30, line=35
	test2: col=30, line=35
	*/

	map_info.map_data = NULL;
	i = 1;
	while (i < argc)
	{
		ft_reset_mapData(&map_info);
		if (argc > 1) // dosya okuma işlemleri
		{
			map_info.file_name = argv[i];
			return_status = ft_col_count_calculate(&map_info, argv[i], 0);
			fd = open(argv[1], O_RDONLY);
			if (fd == -1 || return_status == false ||
				ft_read_map(&map_info, fd) == false)
			{
				ft_puterr("map error\n");
				i++;
				if (fd != -1)
					close(fd);
				continue ;
			}
			ft_print_map(&map_info);
		} 
		// printf("%c\n", map_info.full);
		// printf("%c\n", map_info.obstacle);
		// printf("%c\n", map_info.space);
		// printf("%d\n", map_info.line_len);
		close(fd);
		i++;
	}

	if (argc == 1)
	{
		map_info.file_name = "STDIN";
		return_status = ft_col_count_calculate(&map_info, argv[i], 1);
		fd = STDIN_FILENO;
		if (return_status == false || ft_read_map(&map_info, fd) == false)
		{
			ft_puterr("map error\n");
			return (0);
		}
		ft_print_map(&map_info);
		// printf("%c\n", map_info.full);
		// printf("%c\n", map_info.obstacle);
		// printf("%c\n", map_info.space);
		// printf("%d\n", map_info.line_len);
		close(fd);
	}
	return (0);
}