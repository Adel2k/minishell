/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:15:04 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/07 13:15:06 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*init(int len, char **s)
{
	char	*element;
	int		i;

	i = 0;
	element = malloc((len + 1) * sizeof(char));
	if (!element)
		return (0);
	while (i < len)
	{
		element[i] = (*s)[i];
		i++;
	}
	element[len] = '\0';
	(*s) += len;
	return (element);
}

int	fill_single_quotes(char *s, int len, int flag)
{
	int	flag2;

	flag2 = 0;
	if (s[len] == 39 && flag == 0)
	{
		flag2 = 1;
		len++;
		while (s[len] && s[len] != 39)
			len++;
	}
	else if (s[len] == 39)
	{
		flag2 = 0;
		len++;
	}
	return (len);
}

int	fill_quotes(int len, char *s)
{
	int	flag;

	flag = 0;
	if (s[len] == '"' && flag == 0)
	{
		flag = 1;
		len++;
		while (s[len] && s[len] != '"')
			len++;
	}
	else if (s[len] == '"')
	{
		flag = 0;
		len++;
	}
	len = fill_single_quotes(s, len, flag);
	return (len);
}

static int	fill(char **arr, char *s, int i, int len)
{
	while (*s)
	{
		len = fill_quotes(len, s);
		if (check1(s[len]))
		{
			if (len)
			{
				arr[i] = init(len, &s);
				if (!arr[(++i) - 1])
					return (0);
				len = 0;
			}
			else if (s[len] == ' ' || s[len] == '\0')
				s++;
			if (s[len] == '|' || s[len] == '<' || s[len] == '>')
			{
				if (s[len + 1] && ((s[len] == '<' && s[len + 1] == '<')
						|| (s[len] == '>' && s[len + 1] == '>')))
					arr[i] = init(2, &s);
				else
					arr[i] = init(1, &s);
				if (!arr[(++i) - 1])
					return (0);
				len = 0;
			}
		}
		else if (s[len] != '\0' && s[len] != ' ')
			len++;
		else
			s++;
	}
	return (1);
}

char	**ft_split(char *s)
{
	int		w_count;
	char	**arr;

	if (!s)
		w_count = 0;
	else
		w_count = ft_words_count((char *) s, ' ');
	arr = malloc((w_count + 1) * sizeof(char *));
	if (!arr)
		return (0);
	arr[w_count] = 0;
	if (!w_count)
		return (arr);
	if (!fill(arr, (char *) s, 0, 0))
		return (0);
	return (arr);
}
