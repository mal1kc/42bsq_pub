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

void ft_print_sol(t_bsq_map_data *map_info, t_biggest_sq *biggest_info)
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
		ft_putchar('\n');
		y++;
	}
}
