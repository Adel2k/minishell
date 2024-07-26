/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:04 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/26 14:56:53 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	unset_cut(t_minishell *minishell, t_env *tmp, t_env *prev, int i)
{
	while (tmp)
	{		
		if (ft_strcmp(tmp->key, minishell->cmd[i]) == 0)
		{
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
			break ;
		}
		prev = tmp;
		tmp = tmp -> next;
	}
}

void	unset(t_minishell *minishell, char **cmd)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (!valid_export_arg(cmd[i]))
		{
			err_message("minishell: unset: `", cmd[i],
				"': not a valid identifier\n");
			g_exit_status = 1;
			return ;				
		}
		prev = NULL;
		tmp = minishell->envm;
		unset_cut(minishell, tmp, prev, i);
		i++;
	}
}
