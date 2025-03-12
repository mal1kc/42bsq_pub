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
	@./help_files/map_creater.pl 25000 25000 150 > test_input
	@#time ./help_files/python_ai_sol.py test_input > python_ckt
	@time ./$(NAME) test_input > bizim_ckt
	# @diff python_ckt bizim_ckt && echo "sonuc OK"
	# @echo "---------- Test 0 result: ---------------"
	# @./$(NAME) tests/test2.txt
	# @echo ""
	@#echo "---------- Test 1 result: ---------------"
	@#./$(NAME) tests/test1.txt
	@#echo ""
	@#echo "---------- Test 2 result: ---------------"
	@#./$(NAME) tests/test2.txt
	@#echo ""
	@#echo "---------- Test 3 result: ---------------"
	@#./$(NAME) < tests/test3.txt
	@#echo ""
	@#echo "---------- Test 4 result: ---------------"
	@#./$(NAME) tests/test0.txt tests/test1.txt tests/test2.txt
	@#echo ""

clean:
	@rm -f $(OBJS) test_input python_ckt bizim_ckt

fclean: clean
	@rm -f $(NAME) .stdin_copy_mirac_malik

re: fclean all

.PHONY: all clean fclean test