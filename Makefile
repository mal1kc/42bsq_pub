SRCS = main.c ft_process_map.c
OBJS = $(SRCS:.c=.o)

NAME = bsq

CC = cc
CCFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

main.o: main.c
	$(CC) $(CCFLAGS) -c main.c -o main.o

ft_process_map.o: ft_process_map.c
	$(CC) $(CCFLAGS) -c ft_process_map.c -o ft_process_map.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean