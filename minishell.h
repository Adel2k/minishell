#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_token
{
	char *str;
	char *type;
} t_token;

int	ft_words_count(char *s, char c);
char	**ft_split(char const *s);
size_t	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);
t_token *tokenisation(char **args, int count);
char *find_type(char *str, t_token *tokens, int i);

#endif