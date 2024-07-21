/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:33 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 16:54:55 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut(char c, int *type, int *flag)
{
	if (c == 39)
	{
		if ((*flag) == 0)
		{
			(*type) = 1;
			(*flag) = 1;
		}
		else if ((*flag) == 1 && (*type) == 1)
		{
			(*type) = 0;
			(*flag) = 0;
		}
	}
	if (c == '"')
	{
		if ((*flag) == 0)
		{
			(*type) = 2;
			(*flag) = 1;
		}
		else if ((*flag) == 1 && (*type) == 2)
			(*flag) = 0;
	}
}

int	quotes_type(char *str)
{
	int	i;
	int	type;
	int	flag;

	i = 0;
	type = 0;
	flag = 0;
	while (str[i])
	{
		cut(str[i], &type, &flag);
		if (str[i] == '$')
		{
			if (type == 2 || type == 0)
				return (i);
			if (type == 1 || flag == 1)
			{
				while (str[i] && str[i] != 39)
					i++;
				continue ;
			}
		}
		i++;
	}
	return (-1);
}

char	*find_replacement(t_env *envm, char *s)
{
	while (envm)
	{
		if (ft_strcmp(envm->key, s))
		{
			envm = envm->next;
			continue ;
		}
		return (ft_strdup(envm->value));
		envm = envm->next;
	}
	return (0);
}

int	dollar_sign2(int start, t_token *tokens, int i, t_minishell	*minishell)
{
	char	*s;
	char	*l;

	if (start != -1)
	{
		s = to_find(start, tokens, i);
		if (ft_strlen(s) == 0)
		{
			free(s);
			return (0);
		}
		if (ft_strcmp(s, ft_itoa(getpid())) == 0)
			l = join_trio(tokens[i].str, s, start, start + 2);
		else
		{
			l = join_trio(tokens[i].str, find_replacement(minishell->envm, s),
					start, start + 1 + ft_strlen(s));
			free(s);
		}
			// printf("l = %s\n", l);
			// print_tokens(minishell->tokens, minishell->tokens_count);
		free(tokens[i].str);
		tokens[i].str = l;
		start++;
	}
	return (start);
}

void	dollar_sign(t_token *tokens, int count, t_minishell	*minishell)
{
	int	i;
	int	start;

	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(tokens[i].type, "word"))
			continue ;
		start = 0;
		while ((size_t)start < ft_strlen(tokens[i].str))
		{
			start = quotes_type(tokens[i].str);
			start = dollar_sign2(start, tokens, i, minishell);
			if (start == 0)
				return ;
		}
	}
}
