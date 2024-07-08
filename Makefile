NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./ -g3 -fsanitize=address
LDFLAGS = -lreadline


SRCS = main.c ft_split.c tokenisation.c utils.c word_count.c dollar.c utils2.c free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile minishell.h
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
	