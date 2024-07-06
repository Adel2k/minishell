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
	// word
	// pipe |
	// in_redir <
	// out_redir >
	// heredoc <<
	// append_redir >>
	// in_file after <
	// out_file after >
	// append_file after >>
	// limiter after <<
}	t_token;


////////////////////////tokenisation////////////////////////
t_token	*tokenisation(char **args, int count);
char	*find_type(char *str, t_token *tokens, int i);
void	check_for_invalid_input(t_token *tokens, int count);


////////////////////////utils//////////////////////////////
int		ft_words_count(char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);


////////////////////////ft_split///////////////////////////
char	**ft_split(char const *s);



#endif