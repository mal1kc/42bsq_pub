/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_first_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokcan <mkokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:58:13 by mkokcan           #+#    #+#             */
/*   Updated: 2025/03/12 10:58:13 by mkokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_bool	ft_find_line_len(t_bsq_map_data *map_info, char *buffer)
{
	int	i;
	int	multiples_of_ten;

	multiples_of_ten = 1;
	i = map_info->map_start_index - 4;
	while (i >= 0)
	{
		if (buffer[i] >= '0' && buffer[i] <= '9')
		{
			map_info->line_len += multiples_of_ten * (buffer[i] - '0');
			multiples_of_ten *= 10;
		}
		else
			return (false);
		i--;
	}
	if (map_info->line_len == 0)
		return (false);
	return (true);
}

t_bool	ft_check_three_chars(t_bsq_map_data *map_info, char three_chars[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (three_chars[i] == three_chars[j] && i != j)
				return (false);
			j++;
		}
		if (!(three_chars[i] >= 32 && three_chars[i] <= 126))
			return (false);
		i++;
	}
	map_info->space = three_chars[2];
	map_info->obstacle = three_chars[1];
	map_info->full = three_chars[0];
	return (true);
}

t_bool	ft_save_first_line_info(t_bsq_map_data *map_info, char *buffer)
{
	int		i;
	char	three_chars[3];

	if (map_info->map_start_index < 4)
		return (ft_puterr_and_return(MAP_ERROR_TEXT));
	i = map_info->map_start_index - 1;
	three_chars[0] = buffer[i--];
	three_chars[1] = buffer[i--];
	three_chars[2] = buffer[i--];
	if (ft_check_three_chars(map_info, three_chars) == false)
		return (ft_puterr_and_return(MAP_ERROR_TEXT));
	if (ft_find_line_len(map_info, buffer) == false)
		return (ft_puterr_and_return(MAP_ERROR_TEXT));
	return (true);
}

t_bool	ft_read_checks(t_bsq_map_data *map_info, char *buffer, int i,
		t_bool checks[2])
{
	if (buffer[i] == '\n')
	{
		if (checks[0])
		{
			checks[0] = false;
			if (ft_save_first_line_info(map_info, buffer) == false)
				return (err);
		}
		else
		{
			checks[1] = true;
			return (false);
		}
	}
	else
	{
		if (checks[0])
			map_info->map_start_index++;
		else
			map_info->col_len++;
	}
	return (true);
}

t_bool	ft_read_first_line(t_bsq_map_data *map_info, int fd)
{
	char	buffer[BUFFER_SIZE];
	int		read_bytes;
	int		i;
	t_bool	checks[2];
	t_bool	result;

	checks[0] = true;
	checks[1] = false;
	read_bytes = read(fd, buffer, sizeof(buffer) - 1);
	while (read_bytes > 0 && checks[1] == false)
	{
		buffer[read_bytes] = '\0';
		i = 0;
		while (buffer[i])
		{
			result = ft_read_checks(map_info, buffer, i, checks);
			if (result == false)
				break ;
			else if (result == err)
				return (false);
			i++;
		}
		read_bytes = read(fd, buffer, sizeof(buffer) - 1);
	}
	return (true);
}
