SRCS = main.c extra_func.c reading.c debug.c process.c print_sol.c
OBJS = $(SRCS:.c=.o)

NAME = bsq

CC = clang # unutmaaaaaaaaa
CCFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)
	@# $(CC) $(OBJS) -o $(NAME)
	@echo "Derlendi!"

%.o: %.c
	@# $(CC) -c $< -o $@
	@$(CC) -c $(CCFLAGS) $< -o $@

test: re
	@./help_files/map_creater.pl 200 300 5 > test_input
	@./help_files/python_ai_sol.py test_input > python_ckt
	@./$(NAME) test_input > bizim_ckt
	@diff python_ckt bizim_ckt && echo "sonuc OK"
	@#echo "---------- Test 0 result: ---------------"
	@#./$(NAME) tests/test0.txt
	@#echo ""
	@#echo "---------- Test 1 result: ---------------"
	@#./$(NAME) tests/test1.txt
	@#echo ""
	@#echo "---------- Test 2 result: ---------------"
	@#./$(NAME) tests/test2.txt
	@#echo ""
	@#echo "---------- Test 3 result: ---------------"
	@#./$(NAME) tests/test3.txt
	@#echo ""

clean:
	@rm -f $(OBJS) test_input python_ckt bizim_ckt

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean test
