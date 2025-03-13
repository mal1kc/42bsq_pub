/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokcan <mkokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:57:37 by mkokcan           #+#    #+#             */
/*   Updated: 2025/03/12 10:57:38 by mkokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_bool	ft_is_three_chars(t_bsq_map_data *map_info, char c)
{
	if ((c != map_info->space && c != map_info->obstacle)
		|| c == map_info->full)
		return (false);
	return (true);
}

int	ft_min(t_neighbors *n)
{
	int	min;

	min = n->top;
	if (n->diagonal < min)
		min = n->diagonal;
	if (n->left < min)
		min = n->left;
	return (min);
}

void	ft_map_data_free(t_bsq_map_data *map_info)
{
	int	i;

	if (map_info == NULL || map_info->map_data == NULL)
		return ;
	i = 0;
	while (i < map_info->line_len)
		free(map_info->map_data[i++]);
	free(map_info->map_data);
	map_info->map_data = NULL;
}

void	ft_reset_map_info(t_bsq_map_data *map_info)
{
	ft_map_data_free(map_info);
	map_info->is_stdin = false;
	map_info->line_len = 0;
	map_info->col_len = 0;
	map_info->map_start_index = 0;
	map_info->file_name = "";
	map_info->space = '\0';
	map_info->obstacle = '\0';
	map_info->full = '\0';
	map_info->map_data = NULL;
}

void	ft_reset_biggest_info(t_biggest_sq *biggest_info)
{
	biggest_info->size = 0;
	biggest_info->x = -1;
	biggest_info->y = -1;
}
