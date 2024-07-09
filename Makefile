NAME = term2d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rf -f $(OBJS)

fclean: clean
	rf -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
