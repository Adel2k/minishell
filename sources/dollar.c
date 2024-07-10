/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:33 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/09 15:53:35 by aeminian         ###   ########.fr       */
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

char	*find_replacement(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strstr(env[i], s))
		{
			i++;
			continue ;
		}
		return (ft_strdup(env[i] + ft_strlen(s) + 1));
		i++;
	}
	return (0);
}

void	dollar_sign(t_token *tokens, int count, char **env)
{
	int		i;
	int		start;
	char	*s;
	char	*l;

	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(tokens[i].type, "word"))
			return ;
		start = 0;
		while ((size_t)start < ft_strlen(tokens[i].str))
		{
			start = quotes_type(tokens[i].str);
			if (start != -1)
			{
				s = to_find(start, tokens, i);
				if (ft_strlen(s) == 0)
				{
					free(s);
					return ;
				}
				if (ft_strcmp(s, ft_itoa(getpid())) == 0)
					l = join_trio(tokens[i].str, s, start, start + 2);
				else
				{
					l = join_trio(tokens[i].str, find_replacement(env, s),
					start, start + 1 + ft_strlen(s));
					free(s);	
				}
				free(tokens[i].str);
				tokens[i].str = l;
				start++;
			}
		}
	}
}
