# include "minishell.h"

void unset(t_env *env, char *key)
{
	t_env *prev;

	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			prev->next = env->next;
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
