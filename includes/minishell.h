/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:44 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/09 14:08:48 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

typedef struct s_token
{
	char	*str;
	char	*type;
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

typedef struct s_minishell
{
	t_token	*tokens;
	int		tokens_count;
	char	**env;
	char	**cmd_dirs;
	int		index;
	int (*fd)[2];
	int pipe_count;
	int pipe_index;
	int infile;
	int outfile;
	int if_here_doc;
	int (*here_doc)[2];
}	t_minishell;

////////////////////////tokenisation////////////////////////
t_token	*tokenisation(char **args, int count);
char	*find_type(char *str, t_token *tokens, int i);
void	check_for_invalid_input(t_token *tokens, int count);
void	remove_quotes(t_token *tokens, int count);

////////////////////////utils//////////////////////////////
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strstr(char *str, char *to_find);
void	*ft_memcpy(void *dest, const void *src, size_t n);

////////////////////////utils2//////////////////////////////
char	*ft_strdup(const char *s);
char	*join_trio(char *s, char *s2, int start, int end);
int		check1(char c);
char	*to_find(int start, t_token *tokens, int i);
char	*cut2(char **s, int *len);
char	*ft_itoa(int n);

////////////////////////ft_split_tokens///////////////////////////
char	**ft_split_tokens(char *s);
char	*init_tokens(int len, char **s);

////////////////////////dollar/////////////////////////////
void	dollar_sign(t_token *tokens, int count, char **env);
int		quotes_type(char *str);

////////////////////////free/////////////////////////////
void	free_tokens(t_token *tokens, char *s, int i);
void	err(t_token *tokens, int count, char *message);

////////////////////////words_count/////////////////////////////
int		ft_words_count_tokens(char *s, char c);
void	remove_quotes(t_token *tokens, int count);
void	loop_for_quotes(t_token *tokens, int i, int count);
char	*creating_new(char *old, int start, int j);

////////////////////////error/////////////////////////////
void	malloc_check(void *str);
void	error_handle(void);

////////////////////////commands.c/////////////////////////////
int		count_cmd_args(t_minishell *minishell);
void	run_commands(t_minishell *minishell);

////////////////////////ft_split/////////////////////////////
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);

int pipe_count(t_minishell *minishell);
void	init_fd(t_minishell *minishell);
void pipex(t_minishell *minishell);

int	here_doc(char *limiter, t_minishell *minishell);

#endif