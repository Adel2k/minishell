#include "minishell.h"

char	*ft_strjoin_env(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*s3;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (s1_size + s2_size + 2));
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
	s3[i] = '=';
	i++;
	while (s2[i - s1_size - 1])
	{
		s3[i] = s2[i - s1_size - 1];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char **list_to_array(t_env *env_list)
{
	int len;
	char **env;
	int i;
	
	len = env_len(env_list);
	env = malloc(sizeof(char *) * (len + 1));
	malloc_check(env);
	i = 0;
	while (env_list)
	{
		env[i] = ft_strjoin_env(env_list->key, env_list->value);
		i++;
		env_list = env_list->next;
	}
	return (env);
}

void free_array(char **env)
{
	if (!env)
		return ;
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
void print_env(char **env)
{

	printf("\n\nTHIS IS MY PRINT\n\n");
	if (!env)
		return ;
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
