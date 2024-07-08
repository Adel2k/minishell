/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:44 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/07 13:14:47 by aeminian         ###   ########.fr       */
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

////////////////////////tokenisation////////////////////////
t_token	*tokenisation(char **args, int count);
char	*find_type(char *str, t_token *tokens, int i);
void	check_for_invalid_input(t_token *tokens, int count);
void	remove_quotes(t_token *tokens, int count);

////////////////////////utils//////////////////////////////
int		ft_words_count(char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strstr(char *str, char *to_find);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*join_trio(char *s, char *s2, int start, int end);

////////////////////////utils2//////////////////////////////
char	*ft_strdup(const char *s);
char	*join_trio(char *s, char *s2, int start, int end);
int		check1(char c);
char	*to_find(int start, t_token *tokens, int i);

////////////////////////ft_split///////////////////////////
char	**ft_split(char *s);

////////////////////////dollar/////////////////////////////
void	dollar_sign(t_token *tokens, int count, char **env);
int		quotes_type(char *str);

////////////////////////free/////////////////////////////
void	free_tokens(t_token *tokens, char *s, int i)

#endif
