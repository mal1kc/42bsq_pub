#include "bsq.h"
#include "bsq.h"

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
			print_map_data(&map_info);
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