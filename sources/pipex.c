/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:40 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/12 16:01:20 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_minishell *minishell)
{
	int	i;
	int	count;

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

void	init_fd(t_minishell *minishell)
{
	int	(*fd)[2];
	int	i;

	i = 0;
	fd = malloc(sizeof(int [2]) * (minishell->pipe_count));
	if (!fd)
		err(minishell->tokens, minishell->tokens_count, "Malloc_err\n");
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
			err(minishell->tokens, minishell->tokens_count, "pipe error\n");
		}
		i++;
	}
	minishell->fd = fd;
}

void close_fd(t_minishell *minishell)
{
	int i;

	i = 0;
	while (i < minishell->pipe_count)
	{
		close(minishell->fd[i][0]);
		close(minishell->fd[i][1]);
		i++;
	}
}

void	pipex(t_minishell *minishell)
{
	if (minishell->pipe_index != 0
			&& dup2(minishell->fd[minishell->pipe_index - 1][0], 0) == -1)
	{
		close_fd(minishell);
		err(minishell->tokens, minishell->tokens_count, "pipe error\n");
	}
	if  (minishell->pipe_index < minishell->pipe_count
		&& dup2(minishell->fd[minishell->pipe_index][1], 1) == -1)
	{
		close_fd(minishell);
		err(minishell->tokens, minishell->tokens_count, "pipe error\n");
	}
	close_fd(minishell);
}
