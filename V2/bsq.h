#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>

typedef struct bsq_map_d
{
    
    int line_len;
	int col_len;
    char *file_name;
    char space;
    char obstacle;
    char full;
    char **map_data;
}	bsq_map_d;

void	ft_puterr(char *str);

#endif