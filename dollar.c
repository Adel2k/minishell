#include "minishell.h"

void	cut(char c, int *type, int *flag)
{
	if (c == 39)
	{
		if ((*flag) == 0)
		{
			(*type) = 1;
			(*flag) = 1;
		}
		else if ((*flag) == 1 && (*type) == 1)
		{
			(*type) = 0;
			(*flag) = 0;
		}
	}
	if (c == '"')
	{
		if ((*flag) == 0)
		{
			(*type) = 2;
			(*flag) = 1;
		}
		else if ((*flag) == 1 && (*type) == 2)
			(*flag) = 0;
	}
}


int	quotes_type(char *str)
{
	int	i;
	int	type;
	int	flag;

	i = 0;
	type = 0;
	flag = 0;
	while (str[i])
	{
		cut(str[i], &type, &flag);
		if (str[i] == '$')
		{
			if (type == 2 || type == 0)
				return (i);
			if (type == 1 || flag == 1)
			{
				while (str[i] && str[i] != 39)
					i++;
				continue ;
			}
		}
		i++;
	}
	return (-1);
}

char	*find_replacement(char **env, char *s)
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

void	dollar_sign(t_token *tokens, int count, char **env)
{
	int		i;
	int		start;
	char	*s;
	char	*l;

	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(tokens[i].type, "word"))
			return ;
		start = 0;
		while ((size_t)start < ft_strlen(tokens[i].str))
		{
			start = quotes_type(tokens[i].str);
			printf("start: %d\n", start);
			if (start != -1)
			{
				s = to_find(start, tokens, i);
				l = join_trio(tokens[i].str, find_replacement(env, s),
						start, start + 1 + ft_strlen(s));
				free_tokens(tokens, s, i);
				tokens[i].str = l;
				start++;
			}
		}
			// if (if_dollar(tokens[i].str + start) != -1)
			// {
			// 	start += if_dollar(tokens[i].str + start);
			// 	s = to_find(start, tokens, i);
			// 	// printf("this is unchanged: %s\n", s);
			// 	char *l =	join_trio(tokens[i].str, find_replacement(env, s), start, start + 1 + ft_strlen(s));
			// 	free(tokens[i].str);
			// 	free(s);
			// 	tokens[i].str = l;
			// }
			// else
			// {
			// 	while (tokens[i].str[start])
			// 	{
			// 		if (tokens[i].str[start] == 39)
			// 		{
			// 			start++;
			// 			while (tokens[i].str[start] &&  tokens[i].str[start] != 39)
			// 				start++;
			// 			start++;
			// 			break;
			// 		}
			// 		start++;
			// 	}
			// }
	}
}
