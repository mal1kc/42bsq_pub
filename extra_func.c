#include "bsq.h"

void	ft_puterr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long	temp;

	temp = nb;
	if (temp < 0)
	{
		ft_putchar('-');
		temp = -temp;
	}
	if (temp > 9)
	{
		ft_putnbr(temp / 10);
		ft_putchar(temp % 10 + '0');
	}
	else
	{
		ft_putchar(temp + '0');
	}
}

void	ft_print_map(bsq_map_d *map_info)
{
	int i;
	int j;

	i = 0;
	while (i < map_info->line_len)
	{
		j = 0;
		while (j < map_info->col_len)
		{
			write(1, " ", 1);
			if (map_info->map_data[i][j] != -3 && map_info->map_data[i][j] != -2 && map_info->map_data[i][j] != -1)
				ft_putnbr(map_info->map_data[i][j]);
			else {
				if (map_info->map_data[i][j] == -3)
					ft_putchar(map_info->full);
				else if (map_info->map_data[i][j] == -2)
					ft_putchar(map_info->obstacle);
				else if (map_info->map_data[i][j] == -1)
					ft_putchar(map_info->space);
			}
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}