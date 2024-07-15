#include "minishell.h"

void add_nodes(char *str, t_env **env)
{
	t_env 	*res;
	t_env 	*tmp;
	char	**inf;

	res = malloc(sizeof(t_env));
	malloc_check(res);
	inf = ft_split(str, '=');
	res->info = str;
	res->key = inf[0];
	res->value = inf[1];
	free(inf);
	res->next = NULL;
	if (!*env)
	{
		(*env) = res;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = res;
}

t_env	*init_env(t_minishell *minishell)
{
	t_env 	*res;
	int		i;
	res = NULL;
	i = -1;
	while (minishell->env[++i] != 0)
	{
		add_nodes(ft_strdup(minishell->env[i]), &res);
	}
	return (res);
}

char **init_dirs(t_minishell *minishell)
{
	int		i;
	char	**dirs;

	i = 0;
	while (minishell -> env[i])
	{
		if (ft_strstr_alt(minishell -> env[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(minishell -> env[i] + 5, ':');
	if (!dirs)
	{
		err(minishell, "split_err\n", "");
		return (0);
	}
	return (dirs);
}

int init_cmd_line(t_minishell *minishell, char *input)
{
	char **strs;

	minishell->tokens_count = ft_words_count_tokens(input, ' ');
	strs = ft_split_tokens(input);
	// if (!input)
	// 	exit(printf("No input received.\n"));
	minishell->tokens = tokenisation(strs, minishell->tokens_count);
	free(strs);
	free(input);
	minishell->pipe_count = pipe_count(minishell);
	minishell->pipe_index = 0;
	minishell->index = 0;
	if (init_fd(minishell) < 0)
		return (-1);
	if (check_for_invalid_input(minishell->tokens, minishell->tokens_count) < 0)
		return (-1);
	dollar_sign(minishell->tokens, minishell->tokens_count, minishell);
	remove_quotes(minishell);
	return (1);
}

int	init_fd(t_minishell *minishell)
{
	int	(*fd)[2];
	int	i;

	i = 0;
	fd = malloc(sizeof(int [2]) * (minishell->pipe_count));
	malloc_check(fd);
	while (i < minishell->pipe_count)
	{
		if (pipe(fd[i]) == -1)
		{
			while (i > 0)
			{
				close(fd[i][0]);
				close(fd[i--][1]);
			}
			free(fd);
			err(minishell, "pipe error\n", "");
			return (-1);
		}
		i++;
	}
	minishell->fd = fd;
	return (1);
}
