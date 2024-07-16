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

t_env *creating_new_node(char *key, t_env *env)
{
	t_env *tmp;

	tmp = malloc(sizeof(t_env));
	malloc_check(tmp);
	tmp->key = key;
	tmp->next = NULL;
	while (env->next)
		env = env->next;
	env->next = tmp;
	return (tmp);
}

void export_change(t_env *env, char *str)
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
		tmp = creating_new_node(key, env);
	else
	{
		free(key);
		if (!ft_strchr(str, '='))
			return ;
	}
	free(tmp->value);
	if(ft_strchr(str, '='))
		tmp->value = ft_substr(str, equal_index + 1,
			ft_strlen(str + equal_index - 1));
	else
		tmp->value = NULL;
}

void sorting(t_env *env)
{
    int swapped;
    t_env *ptr1;

    while (1) {
        swapped = 0;
        ptr1 = env;
        while (ptr1->next) {
            if (ft_strcmp(ptr1->key, ptr1->next->key) > 0) { 
                char *temp_key = ptr1->key;
                char *temp_value = ptr1->value;
                ptr1->key = ptr1->next->key;
                ptr1->value = ptr1->next->value;
                ptr1->next->key = temp_key;
                ptr1->next->value = temp_value;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
		if (!swapped)
			break ;
    }
}

void export(t_minishell *minishell, char *str)
{
	if (str[0] && str[0] == '=')
	{
		err_message("export: `", str, "': not a valid identifier");
		return ;
	}
	export_change(minishell->envm, str);
	sorting(minishell->envm);
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
