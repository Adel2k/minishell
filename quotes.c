#include "minishell.h"

void	remove_quotes(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		loop_for_quotes(tokens, i, count);
		i++;
	}
}

void loop_for_quotes(t_token *tokens, int i, int count)
{
	int j;
	int start;
	char *s;
	int c;
	
	j = 0;
	while ((size_t) j < ft_strlen(tokens[i].str))
	{
		if (tokens[i].str[j] == '"' || tokens[i].str[j] == 39)
		{
			start = j;
			c = tokens[i].str[j];
			j++;
			while (tokens[i].str[j] && tokens[i].str[j] != c)
				j++;
			s = creating_new(tokens[i].str, start, j);
			if (!s)
				err(tokens, count, "Malloc error\n");
			free(tokens[i].str);
			tokens[i].str = s;
			j--;
		}
		else
			j++;
	}
}

char *creating_new(char *old, int start, int j)
{
	char *s;
	int k;
	int l;

	s = malloc(ft_strlen(old) - 1);
	if (!s)
		return (0);
	k = 0;
	l = 0;
	while (old[k])
	{
		if (k == start || k == j)
		{
			k++;
			continue ;
		}
		s[l] = old[k];
		k++;
		l++;
	}
	s[l] = 0;
	return (s);
}
