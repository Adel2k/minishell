/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:44 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/20 21:04:37 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

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

void	print_tokens(t_token *tokens, int tokens_count);

////////////////////////tokenisation////////////////////////
t_token	*tokenisation(char **args, int count);
char	*find_type(char *str, t_token *tokens, int i);
int		check_for_invalid_input(t_token *tokens, int count);

//////////////////tokenisation_utils////////////////////////
char	*cut2(char **s, int *len);
int		check1(char c);
char	*join_trio(char *s, char *s2, int start, int end);
char	*to_find(int start, t_token *tokens, int i);

////////////////////////utils//////////////////////////////
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strstr(char *str, char *to_find);
void	*ft_memcpy(void *dest, const void *src, size_t n);

////////////////////////ft_split_tokens///////////////////////////
char	**ft_split_tokens(char *s);
char	*init_tokens(int len, char **s);

////////////////////////dollar/////////////////////////////
void	dollar_sign(t_token *tokens, int count, t_minishell	*minishell);
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
char	**init_dirs(t_minishell *minishell);
int		init_cmd_line(t_minishell *minishell, char *input);
int		init_fd(t_minishell *minishell);
void	init_redirs(t_minishell *minishell);

////////////////////////pipex/////////////////////////////
void	pipex(t_minishell *minishell);
void	close_fd(t_minishell *minishell);

////////////////////////close_free_err/////////////////////////////
void	err_message(char *message1, char *message2, char *message3);
void	close_fd(t_minishell *minishell);
void	waiting_childs(t_minishell *minishell);
void	free_tokens(t_token *tokens, int count);
void	free_cmd(char **command);
void	free_dirs(t_minishell *minishell);

////////////////////////redirs/////////////////////////////
int		open_infile(char *file_name);
int		open_outfile(char *file_name, int i);
void	redirs(t_minishell *minishell);
void	in_redir(t_minishell *minishell);
void	out_redir(t_minishell *minishell);

////////////////////////here_doc/////////////////////////////
int		here_doc(char *limiter, t_minishell *minishell);

////////////////////////utils2//////////////////////////////
char	*ft_strjoin_dirs(char *s1, char *s2);
void	ft_putstr_fd(char *s);
char	*ft_strstr_alt(char *str, char *to_find);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);

////////////////////////utils3//////////////////////////////
void	add_nodes(char *str, t_env **env);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_tolower(char *str);
int		matrix_len(char **array);
char	*ft_strchr(char *s, int c);

////////////////////////builtin/////////////////////////////
int		builtin(t_minishell *minishell, char **command);

////////////////////////cd////////////////////////////////////
void	cd(t_minishell *minishell);

////////////////////////export///////////////////////////////
void	unset(t_env *env, char *key);
void	export(t_minishell *minishell, char *str);
void	export_print(t_env *env);

////////////////////////export///////////////////////////////
char	*ft_itoa(int n);

char	**check_cmd(char **command, t_minishell *minishell);

////////////////////////signals///////////////////////////////
void	signals(void);

void	exit_alt(t_minishell *minishell);
#endif