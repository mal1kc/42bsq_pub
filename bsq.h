#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> // UNUTMA

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
void print_map_data(const bsq_map_d *map);

// reading functions
int	ft_check_first_line(bsq_map_d *map_info, char *first_line);
void	ft_print_map(bsq_map_d *map_info);
t_bool	ft_read_map(bsq_map_d *map_info, int fd);
t_bool ft_check_map_chars(char full, char obstacle, char space);
t_bool ft_read_first_line(bsq_map_d *map_info, char* buffer);
t_bool	ft_col_count_calculate(bsq_map_d *map_info ,char *file_name, int is_stdin);

# define MIN_LEN_FLINE 4
# define MAP_READ_BUFF_SIZE 4096

# define CHAR_FULL 'x'
# define CHAR_OBSTACLE 'o'
# define CHAR_SPACE '.'

#endif