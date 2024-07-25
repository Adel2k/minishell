/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:22 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 20:07:31 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_len(t_env *env) {
    int i;
	
	i = 0;
    while (env)
	{
        i++;
        env = env->next;
    }
    return i;
}

t_env *find_min(t_env *env, t_env *prev_min)
{
	t_env *min;
	
    min = NULL;
    while (env) {
        if ((!prev_min || ft_strcmp(env->key, prev_min->key) > 0) &&
            (!min || ft_strcmp(env->key, min->key) < 0))
            min = env;
        env = env->next;
    }
    return (min);
}

void export_print(t_env *env)
{
    int len;
    t_env *prev_min;
	int k;
	t_env *current_min;
	
	prev_min = NULL;
	len = env_len(env);
	k = 0;
    while(k < len)
	{
        current_min = find_min(env, prev_min);
        if (current_min == NULL)
            break;
        printf("declare -x %s", current_min->key);
        if (current_min->value)
            printf("=\"%s\"", current_min->value);
        printf("\n");
        prev_min = current_min;
		k++;
    }
}

