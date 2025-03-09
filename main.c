#include "bsq.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void ft_reset_mapData(bsq_map_d *mapData)
{
	int i;

	if (mapData->map_data != NULL)
	{
		i = 0;
		while (i < mapData->line_len)
			free(mapData->map_data[i++]);
		free(mapData->map_data);
		mapData->map_data = NULL;		
	}
	
	mapData->line_len = -1;
	mapData->col_len = -1;
	mapData->map_start_index = -1;
	mapData->file_name = "";
	mapData->space = '\0';
	mapData->obstacle = '\0';
	mapData->full = '\0';
	mapData->map_data = NULL;		
}

int	ft_check_first_line(bsq_map_d *mapData, char *first_line)
{
	/* Kontrol edilmesi gerekenler:
	--- karakter eksikse
	--- iki karakter birbiriyle aynıysa
	--- sıkıntı yoksa mapData içerisine bilgiler yazılmalı
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

	mapData->line_len = line_len;
	mapData->space = first_line[0];
	mapData->obstacle = first_line[1];
	mapData->full = first_line[2];

	return (1);
}

int	ft_read_map(bsq_map_d *mapData, int fd)
{
	/* Yapılması gerekenler:
	--- ilk 4 karakterde hata olup olmadığına bakmak ve onları mapData'ya 
	eklemek
	--- col sayısını bulmak
	--- mapData içindeki map_data içerisine malloc ile dizileri oluşturup 
	bilgileri içerisine girmek gerekiyor
	*/
	int bytes_read;
	char buffer[100];
	int i;

	int line_size;

	// 4 karakterden fazla olabilir satır sayısı fazla olabilir
	// onun dışında engel karakteri falan sayı olabilir
	bytes_read = read(fd, buffer, 4);
	buffer[bytes_read] = '\0';
	if (ft_check_first_line(mapData, buffer) == 0)
		return (0);

	line_size = -1;
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';

	}
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
}

t_bool ft_read_first_line(bsq_map_d *mapData, char* buffer)
{
	int i;
	int map_line_len;

	if (mapData->map_start_index < MIN_LEN_FLINE)
		return (false);

	i = mapData->map_start_index - 1;
	mapData->full = buffer[i--];
	mapData->obstacle = buffer[i--];
	mapData->space = buffer[i--];

	if (ft_check_map_chars(mapData->full, mapData->obstacle, mapData->space) == false)
		return (false);

	// 1234.ox
	//    ^
	//    i
	mapData->line_len = 0;
	map_line_len = 1;
	while (i >= 0)
	{
		if (!(buffer[i] >= '0' && buffer[i] <= '9'))
			return (false);
		mapData->line_len += map_line_len * (buffer[i--] - '0');
		map_line_len *= 10;
	}
}

t_bool	ft_col_count_calculate(bsq_map_d *mapData ,char *file_name, int is_stdin)
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
	mapData->map_start_index = 0;
	mapData->col_len = 0;
	while (!r_finish)
	{
		rb = read(fd, buffer, sizeof(buffer) - 1);
		if (rb <= 0)
			break;
		buffer[rb] = '\0';
		while (buffer[rbi])
		{
			if (is_first == true && buffer[rbi] != '\n')
				mapData->map_start_index++;
			if (is_first == false && buffer[rbi] != '\n')
				mapData->col_len++;
			if (is_first == false && buffer[rbi] == '\n')
			{
				r_finish = true;
				break;
			}
			if (buffer[rbi] == '\n' && is_first == true)
			{
				if (ft_read_first_line(mapData, buffer) == false)
					return (false);
				is_first = false;
			}
			rbi++;
		}
	}

	if (mapData->col_len <= 0)
		return (false);
	
	close(fd);
	return (true);
}

int	main(int argc, char **argv)
{
	bsq_map_d mapData;
	int	fd;
	int i;
	t_bool return_status;

	/*
	test0: col=7, line=7
	test1: col=30, line=35
	test2: col=30, line=35
	*/

	mapData.map_data = NULL;
	i = 1;
	while (i < argc)
	{
		ft_reset_mapData(&mapData);
		if (argc > 1) // dosya okuma işlemleri
		{
			mapData.file_name = argv[i];
			return_status = ft_col_count_calculate(&mapData, argv[i], 0);
			fd = open(argv[1], O_RDONLY);
			if (fd == -1 || return_status == false) // Dosya açılamadı
			{
				ft_puterr("map error\n");
				i++;
				continue ;
			}
		} 
		// if (ft_read_map(&mapData, fd) == 0)
		// {
		// 	ft_puterr("map error\n");
		// 	i++;
		// 	continue ;
		// }
		printf("%c\n", mapData.full);
		printf("%c\n", mapData.obstacle);
		printf("%c\n", mapData.space);
		printf("%d\n", mapData.line_len);
		close(fd);
		i++;
	}

	if (argc == 1)
	{
		mapData.file_name = "STDIN";
		return_status = ft_col_count_calculate(&mapData, argv[i], 1);
		fd = STDIN_FILENO;
		if (return_status == false) // Kolon sayısı hesaplanamadı
		{
			ft_puterr("map error\n");
		}
		// if (ft_read_map(&mapData, fd) == 0)
		// {
		// 	ft_puterr("map error\n");
		// 	i++;
		// 	continue ;
		// }
		printf("%c\n", mapData.full);
		printf("%c\n", mapData.obstacle);
		printf("%c\n", mapData.space);
		printf("%d\n", mapData.line_len);
		close(fd);
	}
	/*
	yanlış karakter
	yanlış karakter sayısı
	bozuk numara
	*/
	return 0;
}