/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:12 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 19:35:09 by aeminian         ###   ########.fr       */
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

int valid_export_arg(char *str)
{
	int i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') && str[i] != ' ' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	export(t_minishell *minishell)
{
	int i;

	i = 1;
	while (minishell->cmd[i])
	{
		if ((minishell->cmd[i][0] && (minishell->cmd[i][0] == '=' || ft_strstr_alt(minishell->cmd[i], " ="))) || !valid_export_arg(minishell->cmd[i]))
			err_message("minishell: export: `", minishell->cmd[i], "': not a valid identifier\n");
		else
			export_change(minishell->envm, minishell->cmd[i], 0);
		i++;
	}
	sorting(minishell->envm);
}
