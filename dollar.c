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
		if (quotes_type(s) == 1)
			return (-1);
		i++;
	}
	return (index);
}

int	quotes_type(char *str)
{
	int	i;
	int	type;
	int	flag;

	i = 0;
	type = 0;
	flag = 0;
	while(str[i])
	{
		if (str[i] == 39)
		{
			if(flag == 0)
			{
				type = 1;
				flag = 1;
			}
			else if(flag == 1 && type == 1)
				flag = 0;
		}
		if (str[i] == '"')
		{
			if(flag == 0)
			{
				type = 2;
				flag = 1;
			}
			else if(flag == 1 && type == 2)
				flag = 0;
		}
		if (str[i] == '$')
		{
			if (type == 2 || type == 0)
				return (type);
			if (type == 1 || flag == 1)
			{
				while (str[i] != 39)
					i++;
				break ;
			}
		}
		i++;
	}
	return (type);
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
		if (ft_strcmp(tokens[i].type, "word"))
				return ;
		start = 0;
		while ((size_t)start < ft_strlen(tokens[i].str))
		{
			//int kjnj = quotes_type(tokens[i].str + start);
			// printf("start: %d\n", start);
			if (if_dollar(tokens[i].str + start) != -1)
			{
				start += if_dollar(tokens[i].str + start);
				s = to_find(start, tokens, i);
				// printf("this is unchanged: %s\n", s);
				char *l =	join_trio(tokens[i].str, find_replacement(env, s), start, start + 1 + ft_strlen(s));
				free(tokens[i].str);
				free(s);
				tokens[i].str = l;
			}
			else
			{
				while (tokens[i].str[start])
				{
					if (tokens[i].str[start] == 39)
					{
						start++;
						while (tokens[i].str[start] &&  tokens[i].str[start] != 39)
							start++;
						start++;
						break;
					}
					start++;
				}
			}
			//printf("hello %s   %d\n", tokens[i].str, start);
			// while ((tokens[i].str[start]))
			// {
			// 	if ((tokens[i].str[start] == '$' || tokens[i].str[start] == ' ' || (kjnj == 2 && tokens[i].str[start] == '"') || (kjnj == 1 && tokens[i].str[start] == 39)))
			// 		break;
			// 	// printf("eeeeee %s\n", tokens[i].str + start);
			// 	start++;
			// }
			// printf("hello %s   %d\n", tokens[i].str, start);

		}
		i++;
	}
}
