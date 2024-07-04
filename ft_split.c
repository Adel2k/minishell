#include <minishell.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_words_count(char *s, char c)
{
	int	i;
	int	flag, flag2, flag3;
	int	count;

	i = 0;
	flag = 0;
	flag2 = 0;
	flag3 = 0;
	count = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == '"' && flag2 == 0)
		{
			flag2 = 1;
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (!s[i])
			{
				printf("incu %d\n", i);
				exit(printf("No closing qoute\n"));
			}
		}
		else if(s[i] == '"')
		{
			flag2 = 0;
			i++;
		}
		if (s[i] == 39 && flag2 == 0)
		{
			flag3 = 1;
			i++;
			while (s[i] && s[i] != 39)
				i++;
			if (!s[i])
			{
				exit(printf("No closing qoute\n"));
			}
		}
		else if(s[i] == 39)
		{
			flag3 = 0;
			i++;
		}
		if ((s[i] == c || s[i] == '\0') && flag)
		{
			count++;
			flag = 0;
		}
		else if (s[i] != c)
			flag = 1;
		i++;
	}
	return (count);
}

static char	*init(int len, char *s)
{
	char	*element;
	int		i;

	i = 0;
	element = malloc((len + 1) * sizeof(char));
	if (!element)
		return (0);
	while (i < len)
	{
		element[i] = s[i];
		i++;
	}
	element[len] = '\0';
	return (element);
}

static int	fill(char **arr, char *s, char c)
{
	int	i;
	int	len;
	int flag, flag2;

	i = 0;
	len = 0;
	flag = 0;
	flag2 = 0;
	while (*s)
	{
		if (s[len] == '"' && flag == 0)
		{
			flag = 1;
			len++;
			while (s[len] && s[len] != '"')
				len++;
			if (!s[len])
				exit(printf("No closing qoute\n"));
		}
		else if(s[len] == '"')
		{
			flag = 0;
			len++;
		}
		if (s[len] == 39 && flag == 0)
		{
			flag2 = 1;
			len++;
			while (s[len] && s[len] != 39)
				len++;
			if (!s[len])
				exit(printf("No closing qoute\n"));
		}
		else if(s[len] == 39)
		{
			flag2 = 0;
			len++;
		}
		if ((s[len] == c || s[len] == '\0') && len)
		{
			arr[i] = init(len, s);
			if (!arr[i])
				return (0);
			s += len;
			len = 0;
			i++;
		}
		else if (s[len] != c && s[len] != '\0')
			len++;
		else
			s++;
	}
	return (1);
}

char	**ft_split(char const *s)
{
	int		w_count;
	char	**arr;

	if (!s)
		w_count = 0;
	else
		w_count = ft_words_count((char *) s, ' ');
	arr = malloc((w_count + 1) * sizeof(char *));
	if (!arr)
		return (0);
	arr[w_count] = 0;
	if (!w_count)
		return (arr);
	if (!fill(arr, (char *) s, ' '))
		return (0);
	return (arr);
}
