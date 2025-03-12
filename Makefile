SRCS = ft_extra_func.c ft_print_sol.c ft_read_first_line.c ft_read_map.c main.c test.c
OBJS = $(SRCS:.c=.o)

NAME = bsq

CC = gcc # UNUTMAAA
CCFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)
	@echo "Derlendi!"

%.o: %.c ft.h
	@$(CC) -c $(CCFLAGS) $< -o $@

test: re
	@./help_files/map_creater.pl 250 250 15 > test_input
	@time ./$(NAME) test_input > bizim_ckt
	@time ./help_files/python_ai_sol.py test_input > python_ckt
	@diff python_ckt bizim_ckt && echo "sonuc OK"

clean:
	@rm -f $(OBJS) test_input python_ckt bizim_ckt

fclean: clean
	@rm -f $(NAME) .stdin_copy_mirac_malik

re: fclean all

.PHONY: all clean fclean test