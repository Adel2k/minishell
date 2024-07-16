/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:15:37 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/15 23:06:28 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_quote(char *s, int i, int flag2)
{
	int	flag;

	flag = 0;
	if (s[i] == 39 && flag2 == 0)
	{
		flag = 1;
		i++;
		while (s[i] && s[i] != 39)
			i++;
		if (!s[i])
		{
			err_message(NULL, "No closing qoute\n", "");
			return (-1);
		}
	}
	else if (s[i] == 39)
	{
		flag = 0;
		i++;
	}
	return (i);
}

int	quotes(char *s, int i)
{
	int	flag;

	flag = 0;
	if (s[i] == '"' && flag == 0)
	{
		flag = 1;
		i++;
		while (s[i] && s[i] != '"')
			i++;
		if (!s[i])
		{
			err_message(NULL, "No closing qoute\n", "");
			return (-1);
		}
	}
	else if (s[i] == '"')
	{
		flag = 0;
		i++;
	}
	i = single_quote(s, i, flag);
	return (i);
}

int	if_double(int i, int *count, int *flag, char *s)
{
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
	{
		if (s[i + 1] && ((s[i] == '<' && s[i + 1] == '<')
				|| (s[i] == '>' && s[i + 1] == '>')))
			i++;
		(*count)++;
	}
	if (*flag)
	{
		(*count)++;
		(*flag) = 0;
	}
	return (i);
}

int	ft_words_count_tokens(char *s, char c)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	while (i <= (int)ft_strlen(s))
	{
		i = quotes(s, i);
		if (i < 0)
			return (-1);
		if (s[i] == c || s[i] == '\0' || s[i] == '|'
			|| s[i] == '<' || s[i] == '>')
		{
			i = if_double(i, &count, &flag, s);
		}
		else if (s[i] != c || s[i] != '\0' || s[i] != '|'
			|| s[i] != '<' || s[i] != '>')
			flag = 1;
		i++;
	}
	return (count);
}
