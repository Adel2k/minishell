/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:04 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 08:49:05 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env *env, char *key)
{
	t_env	*prev;

	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			prev->next = env->next;
			if (env->info != NULL)
				free(env->info);
			free(env->key);
			free(env->value);
			free(env);
			break ;
		}
		prev = env;
		env = env -> next;
	}
}
