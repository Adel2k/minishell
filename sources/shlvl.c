#include "minishell.h"

char	*ft_strjoin_shlvl(char *s1, char *s2)
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
	s3 = (char *)malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[i - s1_size])
	{
		s3[i] = s2[i - s1_size];
		i++;
	}
	free(s2);
	s3[i] = '\0';
	return (s3);
}

void change_shlvl(t_minishell *minishell, int how)
{
	int		i;
	char	*num_str;
	int		num;

	i = 0;
	while (minishell->env[i] && !ft_strstr_alt(minishell->env[i], "SHLVL="))
		i++;
	if (minishell->env[i] && ft_strchr(minishell->env[i], '='))
	{
		num = ft_atoi(minishell->env[i] + 6);
		if (how == 0)
		{
			num = 0;
			free(minishell->env[i]);
		}
		else
			num += how;
		num_str = ft_itoa(num);
		minishell->env[i] = ft_strjoin_shlvl("SHLVL=", num_str);
	}
}
