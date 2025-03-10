SRCS = main.c extra_func.c reading.c debug.c process.c
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
	@echo "---------- Test 0 result: ---------------"
	@./$(NAME) tests/test0.txt
	@echo ""
	@echo "---------- Test 1 result: ---------------"
	@./$(NAME) tests/test1.txt
	@echo ""
	@echo "---------- Test 2 result: ---------------"
	@./$(NAME) tests/test2.txt
	@echo ""

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean test
