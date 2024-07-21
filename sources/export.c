/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:12 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 16:33:52 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*creating_new_node(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	malloc_check(tmp);
	tmp->key = key;
	tmp->value = NULL;
	tmp->info = NULL;
	tmp->next = NULL;
	while (env->next)
		env = env->next;
	env->next = tmp;
	return (tmp);
}

void	export_change(t_env *env, char *str, int equal_index)
{
	char	*key;
	t_env	*tmp;

	while (str[equal_index] && str[equal_index] != '=')
		equal_index++;
	key = ft_substr(str, 0, equal_index);
	tmp = env;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp -> next;
	if (!tmp)
		tmp = creating_new_node(key, env);
	else
	{
		free(key);
		if (!ft_strchr(str, '='))
			return ;
	}
	if (tmp->value)
		free(tmp->value);
	if (ft_strchr(str, '='))
		tmp->value = ft_substr(str, equal_index + 1,
				ft_strlen(str + equal_index - 1));
	else
		tmp->value = NULL;
}

void	swich(t_env *ptr1)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = ptr1->key;
	temp_value = ptr1->value;
	ptr1->key = ptr1->next->key;
	ptr1->value = ptr1->next->value;
	ptr1->next->key = temp_key;
	ptr1->next->value = temp_value;
}

void	sorting(t_env *env)
{
	int		swapped;
	t_env	*ptr1;

	while (1)
	{
		swapped = 0;
		ptr1 = env;
		while (ptr1->next)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swich(ptr1);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		if (!swapped)
			break ;
	}
}

void	export(t_minishell *minishell)
{
	int i;

	i = 1;
	while (minishell->cmd[i])
	{
		if (minishell->cmd[i][0] && (minishell->cmd[i][0] == '=' || ft_strstr_alt(minishell->cmd[i], " =")))
			err_message("export: `", minishell->cmd[i], "': not a valid identifier\n");
		else
			export_change(minishell->envm, minishell->cmd[i], 0);
		i++;
	}
	sorting(minishell->envm);
}
