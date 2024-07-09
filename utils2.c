#include "minishell.h"

char	*ft_strdup(const char *s)
{
	const char	*str;
	size_t		size;
	char		*result;

	size = ft_strlen(s);
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	result = (char *)ft_memcpy((void *)str, s, size);
	result[size] = '\0';
	return (result);
}

int	check1(char c)
{
	if ((c == ' ' || c == '\0' || c == '|'
			|| c == '<' || c == '>'))
		return (1);
	return (0);
}


char	*to_find(int start, t_token *tokens, int i)
{
	int	end;

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

char	*join_trio(char *s, char *s2, int start, int end)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(start + ft_strlen(s2) + ft_strlen(s) - end + 1);
	if (!res)
		return (0);
	res[start + ft_strlen(s2) + ft_strlen(s) - end] = 0;
	i = 0;
	while (i < start)
	{
		res[i] = s[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		res[(++i) - 1] = s2[(++j) - 1];
	free(s2);
	while ((size_t) end < ft_strlen(s))
	{
		res[i] = s[end];
		i++;
		end++;
	}
	return (res);
}