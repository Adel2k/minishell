/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:44 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/13 21:11:50 by hrigrigo         ###   ########.fr       */
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
typedef struct s_env
{
	char			*info;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char	**env;
	t_env	*envm;
	char	**cmd_dirs;
	t_token	*tokens;
	int		tokens_count;
	int		index;
	int		(*fd)[2];
	int		pipe_count;
	int		pipe_index;
	int		infile;
	char	*infile_name;
	int		outfile;
	char	*outfile_name;
	int		if_here_doc;
	int		(*here_doc)[2];
	char	**cmd;
}	t_minishell;

////////////////////////tokenisation////////////////////////
t_token	*tokenisation(char **args, int count);
char	*find_type(char *str, t_token *tokens, int i);
int	check_for_invalid_input(t_token *tokens, int count);

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

////////////////////////utils3//////////////////////////////
int		matrix_len(char **array);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strstr_alt(char *str, char *to_find);
char	*ft_strjoin_dirs(char *s1, char *s2);


////////////////////////ft_split_tokens///////////////////////////
char	**ft_split_tokens(char *s);
char	*init_tokens(int len, char **s);

////////////////////////dollar/////////////////////////////
void	dollar_sign(t_token *tokens, int count, char **env);
int		quotes_type(char *str);

////////////////////////words_count/////////////////////////////
int		ft_words_count_tokens(char *s, char c);
void	remove_quotes(t_minishell *minishell);
void	loop_for_quotes(t_token *tokens, int i);
char	*creating_new(char *old, int start, int j);

////////////////////////error/////////////////////////////
void	malloc_check(void *str);
void	error_handle(void);

////////////////////////commands.c/////////////////////////////
int		count_cmd_args(t_minishell *minishell);
int		run_commands(t_minishell *minishell);
char	**cmd_args(t_minishell *minishell);

////////////////////////ft_split/////////////////////////////
char	**ft_split(char const *s, char c);
char	*ft_strjoin_dirs(char *s1, char *s2);
int		pipe_count(t_minishell *minishell);

////////////////////////init/////////////////////////////
t_env	*init_env(t_minishell *minishell);
char 	**init_dirs(t_minishell *minishell);
int		init_cmd_line(t_minishell *minishell, char *input);
int		init_fd(t_minishell *minishell);

////////////////////////pipex/////////////////////////////
void	pipex(t_minishell *minishell);
void close_fd(t_minishell *minishell);

////////////////////////close_free_err/////////////////////////////
void	err(t_minishell *minishell, char *message1, char *message2);
void close_fd(t_minishell *minishell);
void waiting_childs(t_minishell *minishell);
void free_tokens(t_token *tokens, int count);
void err_and_free_tokens(t_token *tokens, int tokens_count, char *message);
void free_cmd(char **command);

////////////////////////redirs/////////////////////////////
int	open_infile(char *file_name);
int	open_outfile(char *file_name, int i);
void init_redirs(t_minishell *minishell);
void redirs(t_minishell *minishell);
void in_redir(t_minishell *minishell);
void out_redir(t_minishell *minishell);

////////////////////////builtin/////////////////////////////
int	builtin(t_minishell *minishell, char **command);

////////////////////////here_doc/////////////////////////////
int	here_doc(char *limiter, t_minishell *minishell);

////////////////////////utils3//////////////////////////////
int	matrix_len(char **array);
void	ft_putstr_fd(char *s);
char	*ft_strjoin(char *s1, char *s2);

#endif