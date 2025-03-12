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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void ft_print_sol(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
{
	int	x;
	int	y;
	int	temp;
	int i;
	char *line_temp = (char *)malloc(sizeof(char) * (map_info->col_len + 1));
	if (line_temp == NULL)
		ft_print_sol2(map_info, biggest_info);

	y = 0;
	while (y < map_info->line_len)
	{
		x = 0;
		i = 0;
		while (x < map_info->col_len)
		{
			temp = map_info->map_data[y][x];
			if (temp == 0)
				line_temp[i] = map_info->obstacle;
			else if ((y >= biggest_info->y - biggest_info->size + 1
				&& y <= biggest_info->y) &&
				(biggest_info->x - biggest_info->size + 1 <= x
				&& biggest_info->x >= x))
				line_temp[i] = map_info->full;
			else
				line_temp[i] = map_info->space;
			x++;
			i++;
		}
		line_temp[i] = '\0';
		write(1, line_temp, map_info->col_len);
		write(1, "\n", 1);
		y++;
	}

	free(line_temp);
}

void ft_print_sol2(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
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
				&& y <= biggest_info->y) &&
				(biggest_info->x - biggest_info->size + 1 <= x
				&& biggest_info->x >= x))
				ft_putchar(map_info->full);
			else
				ft_putchar(map_info->space);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
