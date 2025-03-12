/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokcan <mkokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:58:06 by mkokcan           #+#    #+#             */
/*   Updated: 2025/03/12 10:58:08 by mkokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_bool	ft_is_loc_full(t_biggest_sq *biggest_info, t_location *loc)
{
	return ((loc->y >= biggest_info->y - biggest_info->size + 1
			&& loc->y <= biggest_info->y) && (biggest_info->x
			- biggest_info->size + 1 <= loc->x && biggest_info->x >= loc->x));
}

void	ft_print_sol(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
{
	t_location	loc;
	char		*line_temp;

	line_temp = ft_line_temp_malloc(map_info, biggest_info);
	loc.y = 0;
	while (loc.y < map_info->line_len && line_temp != NULL)
	{
		loc.x = 0;
		while (loc.x < map_info->col_len)
		{
			if (map_info->map_data[loc.y][loc.x] == 0)
				line_temp[loc.x] = map_info->obstacle;
			else if (ft_can_be_full(biggest_info, &loc))
				line_temp[loc.x] = map_info->full;
			else
				line_temp[loc.x] = map_info->space;
			loc.x++;
		}
		line_temp[loc.x] = '\0';
		write(1, line_temp, map_info->col_len);
		write(1, "\n", 1);
		loc.y++;
	}
	free(line_temp);
}

void	ft_print_sol2(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
{
	int	x;
	int	y;
	int	temp;

	y = 0;
	while (y < map_info->line_len)
	{
		x = 0;
		while (x < map_info->col_len)
		{
			temp = map_info->map_data[y][x];
			if (temp == 0)
				ft_putchar(map_info->obstacle);
			else if ((y >= biggest_info->y - biggest_info->size + 1
					&& y <= biggest_info->y) && (biggest_info->x
					- biggest_info->size + 1 <= x && biggest_info->x >= x))
				ft_putchar(map_info->full);
			else
				ft_putchar(map_info->space);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
