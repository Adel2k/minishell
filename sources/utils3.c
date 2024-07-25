/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:50:08 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 18:10:25 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_nodes(char *str, t_env **env)
{
	t_env	*res;
	t_env	*tmp;
	char	**inf;

	res = malloc(sizeof(t_env));
	malloc_check(res);
	inf = ft_split(str, '=');
	res->key = inf[0];
	res->value = inf[1];
	free(inf);
	res->next = NULL;
	if (!*env)
	{
		(*env) = res;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = res;
}

int	ft_tolower(char *str, char *with_whom)
{
	int		i;
	char	*str1;

	str1 = ft_strdup(str);
	i = 0;
	if (!str1)
		return (0);
	while (str1[i])
	{
		if (str1[i] >= 'A' && str1[i] <= 'Z')
			str1[i] += 32;
		i++;
	}
	i = ft_strcmp(str1, with_whom);
	free(str1);
	return (i);
}

int	matrix_len(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
