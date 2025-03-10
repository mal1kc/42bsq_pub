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

void ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
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

int 	ft_get_step(int num)
{
	if (num == 0)
		return (1);
	int i;

	i = 0;
	while(num != 0)
	{
		num /= 10;
		i++;
	}
	return i;
}

void	ft_print_map(bsq_map_d *map_info)
{
	int i;
	int j;
	int temp;
	int total_step_size;

	i = 0;
	total_step_size = map_info->col_len * 4;
	j = 0;
	ft_putstr( "      ");
	while (j < map_info->col_len)
	{
		write(1, "   ", 4 - ft_get_step(j));
		ft_putnbr(j);
		j++;
	}
	ft_putchar('\n');
	j = 0;
	total_step_size += 6;
	while (j < total_step_size)
	{
		j++;
		ft_putchar('-');
	}
	ft_putchar('\n');
	while (i < map_info->line_len)
	{
		ft_putnbr(i);
		write(1, "   ", 4 - ft_get_step(i));
		ft_putstr(" |");
		j = 0;
		while (j < map_info->col_len)
		{
			temp = map_info->map_data[i][j];
			write(1, "   ", 4 - ft_get_step(temp));
			if (temp != -3 && temp != -2 && temp != -1)
				ft_putnbr(temp);
			else {
				if (temp == -3)
					ft_putchar(map_info->full);
				else if (temp == -2)
					ft_putchar(map_info->obstacle);
				else if (temp == -1)
					ft_putchar(map_info->space);
			}
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	ft_print_bsq(biggest_sq *bsq)
{
	ft_putstr("\n biggest sq: ");
	ft_putstr("size: ");
	ft_putnbr(bsq->size);
	ft_putstr(" x: ");
	ft_putnbr(bsq->x);
	ft_putstr(" y: ");
	ft_putnbr(bsq->y);
	ft_putchar('\n');
}