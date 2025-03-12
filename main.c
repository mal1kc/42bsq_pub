/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokcan <mkokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:58:33 by mkokcan           #+#    #+#             */
/*   Updated: 2025/03/12 10:59:07 by mkokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	ft_open_file(t_bsq_map_data *map_info)
{
	int		fd;
	int		is_stdin;
	char	*file_name;

	is_stdin = map_info->is_stdin;
	file_name = map_info->file_name;
	if (is_stdin)
		fd = STDIN_FILENO;
	else
		fd = open(file_name, O_RDONLY);
	return (fd);
}

void	ft_solition(t_bsq_map_data *map_info, t_biggest_sq *biggest_info,
		char *file_name, t_bool is_stdin)
{
	int	fd;

	map_info->map_data = NULL;
	ft_reset_map_info(map_info);
	ft_reset_biggest_info(biggest_info);
	map_info->file_name = file_name;
	map_info->is_stdin = is_stdin;
	fd = ft_open_file(map_info);
	if (fd != STDIN_FILENO && fd == -1)
	{
		ft_puterr_and_return(MAP_ERROR_TEXT);
		return ;
	}
	else
	{
		if (ft_read_first_line(map_info, fd))
			if (ft_read_map(map_info, biggest_info))
				ft_print_sol(map_info, biggest_info);
		close(fd);
	}
}

void	ft_create_stdin_file(void)
{
	int		fd_stdin;
	int		fd_outfile;
	char	buffer[BUFFER_SIZE];
	int		bytes_read;

	fd_stdin = STDIN_FILENO;
	fd_outfile = open(STDIN_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	bytes_read = read(fd_stdin, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		write(fd_outfile, buffer, bytes_read);
		bytes_read = read(fd_stdin, buffer, BUFFER_SIZE);
	}
	close(fd_outfile);
}

int	main(int argc, char **argv)
{
	t_bsq_map_data	map_info;
	t_biggest_sq	biggest_info;
	int				i;

	if (argc == 1)
	{
		ft_create_stdin_file();
		ft_solition(&map_info, &biggest_info, STDIN_FILE_NAME, false);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			ft_solition(&map_info, &biggest_info, argv[i], false);
			i++;
		}
	}
	return (0);
}
