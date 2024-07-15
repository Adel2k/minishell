/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:40 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/15 23:06:28 by hrigrigo         ###   ########.fr       */
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

void	pipex(t_minishell *minishell)
{
	if (minishell->pipe_index != 0 && minishell->infile == 0
			&& dup2(minishell->fd[minishell->pipe_index - 1][0], 0) == -1)
	{
		close_fd(minishell);
		err_message("minishell: ", "pipe error\n", "");
		exit(1);
	}
	if  (minishell->pipe_index < minishell->pipe_count
		&& dup2(minishell->fd[minishell->pipe_index][1], 1) == -1)
	{
		close_fd(minishell);
		err_message("minishell: ", "pipe error\n", "");
		exit(1);
	}
	close_fd(minishell);
}
