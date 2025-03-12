/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokcan <mkokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:58:24 by mkokcan           #+#    #+#             */
/*   Updated: 2025/03/12 10:58:25 by mkokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/*
3- İçeriklerin okunup, sayılar yazılması, bigest bulunması lazım
	- Dosyanın tekrardan açılması lazım
	- satır uzunluklarının eşitliğinin kontrolü
	- haritanın sadece .ox'lerden oluştuğunun kontrolü
	- Eğer haritada sorun varsa map error ve sonraki harita
*/

void	ft_calculate_neighbors(t_bsq_map_data *map_info, t_biggest_sq *biggest_info, t_location *loc, t_neighbors *n)
{
	int result;

	n->top = 0;
	n->diagonal = 0;
	n->left = 0;
	if (loc->y == 0 && loc->x == 0)
		n->left = 0;
	else if (loc->y == 0)
		n->left = map_info->map_data[loc->y][loc->x - 1];
	else if (loc->x == 0)
		n->top = map_info->map_data[loc->y - 1][loc->x];
	else {
		n->top = map_info->map_data[loc->y - 1][loc->x];
		n->diagonal = map_info->map_data[loc->y - 1][loc->x - 1];
		n->left = map_info->map_data[loc->y][loc->x - 1];
	}
	result = ft_min(n) + 1;
	if (biggest_info->size < result)
	{
		biggest_info->size = result;
		biggest_info->x = loc->x;
		biggest_info->y = loc->y;
	}
}

t_bool	ft_write_map_data(t_bsq_map_data *map_info, t_biggest_sq *biggest_info,
	t_location *loc, char *buffer)
{
	t_neighbors n;

	while (*buffer)
	{
		if (*buffer == '\n')
		{
			loc->y++;
			if (loc->x != map_info->col_len)
				return (false);
			loc->x = 0;
			buffer++;
			continue;
		}
		if (loc->x >= map_info->col_len || loc->y >= map_info->line_len)
			return (false);
		if (ft_is_three_chars(map_info, *buffer) == false)
			return (false);
		if (*buffer == map_info->obstacle)
			map_info->map_data[loc->y][loc->x] = 0;
		else {
			ft_calculate_neighbors(map_info, biggest_info, loc, &n);
			map_info->map_data[loc->y][loc->x] = ft_min(&n) + 1;
		}
		loc->x++;
		buffer++;
	}

	return (true);
}

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

t_bool	ft_save_map_data(t_bsq_map_data *map_info, t_biggest_sq *biggest_info, int fd)
{
	int		read_bytes;
	char	buffer[BUFFER_SIZE];
	t_location loc;
	char *temp;
	t_bool is_first_line;

	is_first_line = true;
	if (ft_map_data_malloc(map_info) == false)
		return (false);
	loc.x = 0;
	loc.y = 0;
	read_bytes = read(fd, buffer, sizeof(buffer) - 1);
	while (read_bytes > 0){
		buffer[read_bytes] = '\0';
		temp = &buffer[0];
		if (is_first_line == true)
		{
			temp += map_info->map_start_index + 1;
			is_first_line = false;
		}
		if (ft_write_map_data(map_info, biggest_info, &loc, temp) == false)
		{
			ft_map_data_free(map_info);
			return (false);
		}
		read_bytes = read(fd, buffer, sizeof(buffer) - 1);
	}
	if (loc.y != map_info->line_len)
		return (false);
	if (map_info->ist_obs == false)
		return (false);
	return (true);
}

t_bool	ft_read_map(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
{
	int	fd;

	fd = ft_open_file(map_info);
	if (fd == -1)
	{
		return ft_puterr_and_return(MAP_ERROR_TEXT);
	}
	else
	{
		if (ft_save_map_data(map_info, biggest_info, fd) == false)
			return (ft_puterr_and_return(MAP_ERROR_TEXT));
		close(fd);
	}

	return (true);
}
