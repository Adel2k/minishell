#include "minishell.h"

int	if_dollar(char *s)
{
	int i;
	int	index;

	i = 0;
	while(s[i])
	{
		if(s[i] == '$')
		{
			index = i;
			break;
		}
		i++;
	}
	if (!s[i] || !s[i + 1])
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == 39 && i < index)
			return (-1);
		i++;
	}
	return (index);
}

char *to_find(int start, t_token *tokens, int i)
{
	int end;

	end = start + 1;
	while (tokens[i].str[end])
	{
		if (tokens[i].str[end] == ' ' || tokens[i].str[end] == 39
			|| tokens[i].str[end] == '"' || tokens[i].str[end] == '$')
		{
			end--;
			break ;
		}
		end++;
	}
	return (ft_substr(tokens[i].str, start + 1, end - start));
}

char *find_replacement(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strstr(env[i], s))
		{
			i++;
			continue ;
		}
		return (ft_strdup(env[i] + ft_strlen(s) + 1));
		i++;
	}
	return (0);
}

void dollar_sign(t_token *tokens, int count, char **env)
{
	int	i;
	int start;
	char *s;

	i = 0;
	while (i < count)
	{
		start = 0;
		while ((size_t)start < ft_strlen(tokens[i].str))
		{
			start = if_dollar(tokens[i].str);
			if (ft_strcmp(tokens[i].type, "word") || start == -1)
				return ;
			s = to_find(start, tokens, i);
			char *l =	join_trio(tokens[i].str, find_replacement(env, s), start, start + 1 + ft_strlen(s));
			free(tokens[i].str);
			free(s);
			tokens[i].str = l;
			start++;
		}
		i++;
	}
}
