/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:21 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 15:34:32 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check1(char c)
{
	if ((c == ' ' || c == '\0' || c == '|'
			|| c == '<' || c == '>'))
		return (1);
	return (0);
}

char	*to_find(int start, t_token *tokens, int i)
{
	int	end;
	int	pid;

	end = start + 1;
	pid = getpid();
	if (tokens[i].str[end] == '$')
		return (ft_itoa(pid));
	while (tokens[i].str[end])
	{
		if (tokens[i].str[end] == ' ' || tokens[i].str[end] == 39
			|| tokens[i].str[end] == '"' || tokens[i].str[end] == '$'
			|| tokens[i].str[end] == '/' || tokens[i].str[end] == '=')
		{
			end--;
			break ;
		}
		end++;
	}
	return (ft_substr(tokens[i].str, start + 1, end - start));
}

char	*join_trio(char *s, char *s2, int start, int end)
{
	char	*res;
	int		i;
	int		j;

	if (!s || !s2)
		return (0);
	res = malloc(start + ft_strlen(s2) + ft_strlen(s) - end + 1);
	malloc_check(res);
	res[start + ft_strlen(s2) + ft_strlen(s) - end] = 0;
	i = -1;
	while (++i < start)
		res[i] = s[i];
	j = 0;
	while (s2 && s2[j])
		res[(++i) - 1] = s2[(++j) - 1];
	free(s2);
	while ((size_t) end < ft_strlen(s))
	{
		res[i] = s[end];
		i++;
		end++;
	}
	return (res);
}

char	*cut2(char **s, int *len)
{
	if ((*s)[*len] == '|' || (*s)[*len] == '<' || (*s)[*len] == '>')
	{
		if ((*s)[*len + 1] && (((*s)[*len] == '<' && (*s)[*len + 1] == '<')
				|| ((*s)[*len] == '>' && (*s)[*len + 1] == '>')))
			return (init_tokens(2, s));
		else
			return (init_tokens(1, s));
		*len = 0;
	}
	return (0);
}
