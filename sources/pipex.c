#include "minishell.h"

int pipe_count(t_minishell *minishell)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < minishell->tokens_count)
	{
		if (!ft_strcmp(minishell->tokens[i].type, "pipe"))
			count++;
		i++;
	}
	return (count);
}


void pipex(t_minishell *minishell)
{
	int fd[2];
	if (pipe(fd) == -1)
		err(minishell->tokens, minishell->tokens_count, "pipe failed");
	if (pipe_count > 0)
	{
		
	}
}