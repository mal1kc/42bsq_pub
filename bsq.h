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
    int map_start_index;
}	bsq_map_d;

typedef enum t_bool
{
    false,
    true
} t_bool;

void	ft_puterr(char *str);

# define MIN_LEN_FLINE 4

#endif