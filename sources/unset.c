/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:04 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/22 16:14:16 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_minishell *minishell, char **cmd)
{
	t_env	*prev;
	t_env *tmp;
	int i;

	i = 0;
	while (cmd[i])
	{
		prev = NULL;
		tmp = minishell->envm;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, cmd[i]) == 0)
			{
				if (!prev)
				{
					tmp = tmp->next;
					free(minishell->envm->key);
					free(minishell->envm->value);
					free(minishell->envm);
					minishell->envm = tmp;
					break ;
				}
				prev->next = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp -> next;
		}
		i++;
	}
}
