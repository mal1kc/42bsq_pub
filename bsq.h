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
    int **map_data;
}	bsq_map_d;

typedef struct biggest_sq
{
	int size;
	int x;
	int y;
} biggest_sq;

typedef enum t_bool
{
    false,
    true
} t_bool;


// reading functions
int	ft_check_first_line(bsq_map_d *map_info, char *first_line);
void	ft_print_map(bsq_map_d *map_info);
t_bool	ft_read_map(bsq_map_d *map_info, int fd);
t_bool ft_check_map_chars(char full, char obstacle, char space);
t_bool ft_read_first_line(bsq_map_d *map_info, char* buffer);
t_bool	ft_col_count_calculate(bsq_map_d *map_info ,char *file_name, int is_stdin);

// extra_func
void	ft_puterr(char *str);
void	ft_putchar(char c);
void ft_putstr(char *str);
void	ft_putnbr(int nb);
int 	ft_get_step(int num);
void	ft_print_map(bsq_map_d *map_info);
void	ft_print_bsq(biggest_sq *bsq);

// debug.c
void print_map_data(const bsq_map_d *map);

// process.c
t_bool	check_below(bsq_map_d *map_info,  biggest_sq *bsq, biggest_sq *check_sq);
void	process_map(bsq_map_d *map_info, biggest_sq *bsq);

# define MIN_LEN_FLINE 4
# define MAP_READ_BUFF_SIZE 4096

# define CHAR_FULL -3
# define CHAR_OBSTACLE -2
# define CHAR_SPACE -1

// # define CHAR_FULL 'x'
// # define CHAR_OBSTACLE 'o'
// # define CHAR_SPACE '.'

#endif