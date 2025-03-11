#ifndef BSQ_H
# define BSQ_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define MAP_ERROR_TEXT "map error\n"
# define BUFFER_SIZE 4096
# define STDIN_FILE_NAME "stdin_251654.txt"
// # define CHAR_FULL -3
// # define CHAR_OBSTACLE -2
// # define CHAR_SPACE -1

typedef enum e_bool
{
    false,
    true,
    err
} t_bool;

typedef struct s_bsq_map_data
{
    
	t_bool is_stdin;
    int line_len;
	int col_len;
    int map_start_index;
    char *file_name;
    char space;
    char obstacle;
    char full;
    int **map_data;
}	t_bsq_map_data;

typedef struct s_biggest_sq
{
	int size;
	int x;
	int y;
} t_biggest_sq;

typedef struct s_location
{
    int x;
    int y;
}   t_location;

typedef struct s_neighbors
{
    int left;
    int top;
    int diagonal;
}   t_neighbors;

/* Fonksiyon Prototipleri */
// main.c
int	ft_open_file(t_bsq_map_data *map_info);
void	ft_soliton(t_bsq_map_data *map_info, t_biggest_sq *biggest_info,
	char *file_name, t_bool is_stdin);

// ft_extra_func.c
t_bool	ft_is_three_chars(t_bsq_map_data *map_info, char c);
int	ft_min(t_neighbors *n);
void	ft_map_data_free(t_bsq_map_data *map_info);
void	ft_reset_map_info(t_bsq_map_data *map_info);
void	ft_reset_biggest_info(t_biggest_sq *biggest_info);
t_bool	ft_puterr_and_return(char *str);

// ft_read_first_line.c
t_bool	ft_find_line_len(t_bsq_map_data *map_info, char *buffer);
t_bool ft_check_three_chars(t_bsq_map_data *map_info, char three_chars[3]);
t_bool	ft_save_first_line_info(t_bsq_map_data *map_info, char *buffer);
t_bool	ft_read_checks(t_bsq_map_data *map_info, char *buffer, int i, t_bool checks[2]);
t_bool ft_read_first_line(t_bsq_map_data *map_info, int fd);

// ft_read_map.c
void    ft_calculate_neighbors(t_bsq_map_data *map_info, t_biggest_sq *biggest_info, t_location *loc, t_neighbors *n);
t_bool	ft_write_map_data(t_bsq_map_data *map_info, t_biggest_sq *biggest_info,
	t_location *loc, char *buffer);
t_bool	ft_map_data_malloc(t_bsq_map_data *map_info);
t_bool	ft_save_map_data(t_bsq_map_data *map_info, t_biggest_sq *biggest_info, int fd);
t_bool	ft_read_map(t_bsq_map_data *map_info, t_biggest_sq *biggest_info);

// ft_print_sol.c
void	ft_putchar(char c);
void ft_print_sol(t_bsq_map_data *map_info, t_biggest_sq *biggest_info);

// test.c
void	ft_print_map_info(t_bsq_map_data *map_info, t_biggest_sq *biggest_info);
int	ft_step_size(int nbr);
void	ft_4_basamak_yazdir(int nbr);
void	ft_print_map_data(t_bsq_map_data *map_info);
void	ft_print_biggest(t_biggest_sq *biggest_info);

#endif
