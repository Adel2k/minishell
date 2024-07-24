/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:12:16 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 15:12:51 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_minishell *minishell, char *old, char *new)
{
	t_env	*start;

	start = minishell->envm;
	while (minishell->envm)
	{
		if (ft_strcmp(minishell->envm->key, "PWD") == 0)
		{
			free(minishell->envm->value);
			minishell->envm->value = ft_strdup(new);
		}
		if (ft_strcmp(minishell->envm->key, "OLDPWD") == 0)
		{
			free(minishell->envm->value);
			minishell->envm->value = ft_strdup(old);
		}
		minishell->envm = minishell->envm->next;
	}
	minishell->envm = start;
}

int	check_newline(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == 0 || str[i] != '-')
		return (0);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] == 'n' && (str[i + 1] == 'n'
				|| str[i + 1] == ' ' || str[i + 1] == 0))
		{
			if (str[i + 1] == 0)
				return (1);
			i++;
		}
	}
	return (0);
}