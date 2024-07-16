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
