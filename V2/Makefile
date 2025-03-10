SRCS = ft_extra_func.c ft_read_first_line.c ft_read_map.c main.c test.c
OBJS = $(SRCS:.c=.o)

NAME = bsq

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)
	@echo "Derlendi!"

%.o: %.c
	@$(CC) -c $(CCFLAGS) $< -o $@

test: re
	@echo "---------- Test 0 result: ---------------"
	@./$(NAME) tests/test0.txt
	@echo ""
	@echo "---------- Test 1 result: ---------------"
	@./$(NAME) tests/test1.txt
	@echo ""
	@echo "---------- Test 2 result: ---------------"
	@./$(NAME) tests/test2.txt
	@echo ""
	@echo "---------- Test 3 result: ---------------"
	@./$(NAME) < tests/test3.txt
	@echo ""
	@echo "---------- Test 4 result: ---------------"
	@./$(NAME) tests/test0.txt tests/test1.txt tests/test2.txt
	@echo ""

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean test