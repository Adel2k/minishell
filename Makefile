NAME = minishell

READLINE = readline
CC = cc

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) -g3 -fsanitize=address
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = 	includes/minishell.h \

SRCS_DIR = sources/

OBJS_DIR = objects/

SRCS_NAME = main.c ft_split_tokens.c error_handle.c tokenisation.c ft_itoa.c utils.c word_count.c dollar.c utils2.c free.c quotes.c ft_split.c

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tokenization
	@mkdir -p $(OBJS_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

re: fclean all

.PHONY: all clean fclean re