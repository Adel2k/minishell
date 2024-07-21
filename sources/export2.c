/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:22 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 18:37:11 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print(t_env *env)
{
	while (env)
	{
		write(1, "declare -x ", 12);
		write(1, env->key, ft_strlen(env->key));
		if (env->value)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env = env->next;
	}
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
