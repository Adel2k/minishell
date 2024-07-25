/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:04 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 18:09:54 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cut(t_minishell *minishell, t_env *tmp, t_env *prev)
{
	if (ft_strcmp(tmp->key, "SHLVL") == 0)
	{
		change_shlvl(minishell, 0);
	}
	if (!prev)
	{
		tmp = tmp->next;
		free(minishell->envm->key);
		free(minishell->envm->value);
		free(minishell->envm);
		minishell->envm = tmp;
		return ;
	}
	prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	unset(t_minishell *minishell, char **cmd)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		prev = NULL;
		tmp = minishell->envm;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, cmd[i]) == 0)
			{
				unset_cut(minishell, tmp, prev);
				break ;
			}
			prev = tmp;
			tmp = tmp -> next;
		}
		i++;
	}
}
