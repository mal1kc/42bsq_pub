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

void	ft_calculate_neighbors(t_bsq_map_data *map_info,
		t_biggest_sq *biggest_info, t_location *loc, t_neighbors *n)
{
	int	result;

	n->top = 0;
	n->diagonal = 0;
	n->left = 0;
	if (loc->y == 0 && loc->x == 0)
		n->left = 0;
	else if (loc->y == 0)
		n->left = map_info->map_data[loc->y][loc->x - 1];
	else if (loc->x == 0)
		n->top = map_info->map_data[loc->y - 1][loc->x];
	else
	{
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

t_bool	ft_write_map_data_helper2(t_bsq_map_data *map_info,
	t_location *loc, char buffer_char)
{
	if (buffer_char == map_info->obstacle)
	{
		map_info->map_data[loc->y][loc->x] = 0;
		return (true);
	}
	return (false);
}

t_bool	ft_write_map_data(t_bsq_map_data *map_info, t_biggest_sq *bqi,
		t_location *loc, char *buffer)
{
	t_neighbors	n;

	while (*buffer)
	{
		if (*buffer == '\n')
		{
			loc->y++;
			if (loc->x != map_info->col_len)
				return (false);
			loc->x = 0;
			buffer++;
			continue ;
		}
		if (!ft_write_map_data_helper(map_info, *buffer, loc))
			return (false);
		if (!ft_write_map_data_helper2(map_info, loc, *buffer))
		{
			ft_calculate_neighbors(map_info, bqi, loc, &n);
			map_info->map_data[loc->y][loc->x] = ft_min(&n) + 1;
		}
		loc->x++;
		buffer++;
	}
	return (true);
}

t_bool	ft_save_map_data(t_bsq_map_data *map_info, t_biggest_sq *biggest_info,
		int fd)
{
	t_location	loc;

	if (ft_map_data_malloc(map_info) == false)
		return (false);
	loc.x = 0;
	loc.y = 0;
	if (ft_save_data_helper(map_info, biggest_info, fd, &loc) == false)
		return (false);
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
		return (ft_puterr_and_return(MAP_ERROR_TEXT));
	}
	else
	{
		if (ft_save_map_data(map_info, biggest_info, fd) == false)
			return (ft_puterr_and_return(MAP_ERROR_TEXT));
		close(fd);
	}
	return (true);
}
