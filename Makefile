CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./
LDFLAGS = -lreadline

NAME = minishell

SRCS = main.c

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
	