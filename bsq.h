#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>

typedef struct bsq_map_d
{
    
    int line_len;
	int col_len;
    int map_start_index;
    char *file_name;
    char space;
    char obstacle;
    char full;
    char **map_data;
}	bsq_map_d;

typedef enum t_bool
{
    false,
    true
} t_bool;

void	ft_puterr(char *str);

# define MIN_LEN_FLINE 4
# define MAP_READ_BUFF_SIZE 4096

# define CHAR_FULL 'x'
# define CHAR_OBSTACLE 'o'
# define CHAR_SPACE '.'

#endif