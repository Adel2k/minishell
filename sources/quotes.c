/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:10:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/09 19:10:59 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->tokens_count)
	{
		loop_for_quotes(minishell->tokens, i);
		i++;
	}
}

void	loop_for_quotes(t_token *tokens, int i)
{
	int		j;
	int		start;
	char	*s;
	int		c;

	j = 0;
	while ((size_t) j < ft_strlen(tokens[i].str))
	{
		if (tokens[i].str[j] == '"' || tokens[i].str[j] == 39)
		{
			start = j;
			c = tokens[i].str[j];
			j++;
			while (tokens[i].str[j] && tokens[i].str[j] != c)
				j++;
			s = creating_new(tokens[i].str, start, j);
			free(tokens[i].str);
			tokens[i].str = s;
			j--;
		}
		else
			j++;
	}
}

char	*creating_new(char *old, int start, int j)
{
	char	*s;
	int		k;
	int		l;

	s = malloc(ft_strlen(old) - 1);
	malloc_check(s);
	k = 0;
	l = 0;
	while (old[k])
	{
		if (k == start || k == j)
		{
			k++;
			continue ;
		}
		s[l] = old[k];
		k++;
		l++;
	}
	s[l] = 0;
	return (s);
}
