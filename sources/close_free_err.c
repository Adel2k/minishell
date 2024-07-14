/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:07 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/09 15:53:09 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err(t_minishell *minishell, char *message)
{
	free_tokens(minishell->tokens, minishell->tokens_count);
	free_cmd(minishell->cmd);
	close_fd(minishell);
	if (minishell->pipe_count != 0)
		free(minishell->fd);
	if (minishell->if_here_doc != 0)
		waiting_childs(minishell);
	exit(printf("%s", message));
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

void waiting_childs(t_minishell *minishell)
{
	int k;
	
	k = 0;
	while (k < minishell->pipe_count + 1)
	{
		waitpid(-1, NULL, 0); // AVELACNEL STATUSI STUGUM(2RD ARGUMENT)
		k++;
	}
}

void free_tokens(t_token *tokens, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(tokens[j].str);
		j++;
	}
	free(tokens);
}

void err_and_free_tokens(t_token *tokens, int tokens_count, char *message)
{
	free_tokens(tokens, tokens_count);
	exit(printf("%s", message));
}
void free_cmd(char **command)
{
	int i;

	if (!command)
		return ;
	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}
