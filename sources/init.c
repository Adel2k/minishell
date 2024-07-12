#include "minishell.h"

void add_nodes(char *str, t_env **env)
{
	t_env 	*res;
	t_env 	*tmp;
	char	**inf;

	res = malloc(sizeof(t_env));
	malloc_check(res);
	inf = ft_split(str, '=');
	res->info = str;
	res->key = inf[0];
	res->value = inf[1];
	free(inf);
	res->next = NULL;
	if (!*env)
	{
		(*env) = res;
		return ;
	}
	tmp = *env;
	printf("%d\n", __LINE__);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = res;
}

t_env	*init_env(t_minishell *minishell)
{
	t_env 	*res;
	int		i;
	res = NULL;
	i = -1;
	while (minishell->env[++i] != 0)
	{
		add_nodes(ft_strdup(minishell->env[i]), &res);
	}
	return (res);
}
