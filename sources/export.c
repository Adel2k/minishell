#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}

void export(t_env *env, char *str)
{
	int equal_index;
	char *key;
	t_env *tmp;

	equal_index = 0;
	while (str[equal_index] && str[equal_index] != '=')
		equal_index++;
	key = ft_substr(str, 0, equal_index);
	tmp = env;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp -> next;
	if (!tmp)
	{
		tmp = malloc(sizeof(t_env));
		malloc_check(tmp);
		tmp->key = key;
		tmp->next = NULL;
		while (env->next)
			env = env->next;
		env->next = tmp;
	}
	else
		free(key);
	free(tmp->value);
	if(ft_strchr(str, '='))
		tmp->value = ft_substr(str, equal_index + 1, ft_strlen(str + equal_index - 1));
	else
		tmp->value = NULL;
}

void export_print(t_env *env)
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
