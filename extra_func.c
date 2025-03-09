#include "bsq.h"

void	ft_puterr(char *str)
{
	while (*str)
		write(2, str++, 1);
}