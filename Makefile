SRCS = ft_allocating.c ft_extra_func.c ft_print_sol.c ft_read_first_line.c ft_read_helpers.c ft_read_map.c ft_write_funcs.c main.c
OBJS = $(SRCS:.c=.o)

NAME = bsq

CC = cc
CCFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

%.o: %.c ft.h
	$(CC) -c $(CCFLAGS) $< -o $@

test: re
	@./help_files/map_creater.pl 250 250 15 > test_input
	@time ./$(NAME) test_input > bizim_ckt
	@time ./help_files/python_ai_sol.py test_input > python_ckt
	@diff python_ckt bizim_ckt && echo "sonuc OK"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) .stdin_copy_mirac_malik

re: fclean all

.PHONY: all clean fclean test