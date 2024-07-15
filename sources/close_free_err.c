/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:07 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/15 23:10:00 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_message(char *message1, char *message2, char *message3)
{
	write(2, message1, ft_strlen(message1));
	write(2, message2, ft_strlen(message2));
	write(2, message3, ft_strlen(message3));
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
	// if (minishell->infile > 0)
	// 	close(minishell->infile);
	// if (minishell->outfile > 1)
	// 	close(minishell->outfile);
	// if (minishell->if_here_doc == 1)
	// {
	// 	close((*minishell->here_doc)[0]);
	// 	close((*minishell->here_doc)[1]);
	// }
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
	//printf("minishell->tokens freed\n");	
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
	//printf("minishell->cmd freed\n");
}
