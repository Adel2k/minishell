/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:56:05 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 21:18:24 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	malloc_check(void *str)
{
	if (!str)
		error_handle();
}

void	error_handle(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	err_message(char *message1, char *message2, char *message3)
{
	write(2, message1, ft_strlen(message1));
	write(2, message2, ft_strlen(message2));
	write(2, message3, ft_strlen(message3));
}

void	close_fd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->pipe_count)
	{
		close(minishell->fd[i][0]);
		close(minishell->fd[i][1]);
		i++;
	}
}

void	waiting_childs(t_minishell *minishell)
{
	int	k;
	int	exit_s;

	k = 0;
	// if (minishell->pipe_count == 0 && minishell->is_builtin == 1)
	// 	return ;
	while (k < minishell->pipe_count + 1)
	{
		waitpid(-1, &exit_s, 0);
		if ((WTERMSIG(exit_s)) == 3)
			printf("Quit : 3\n");
		else if (WIFEXITED(exit_s))
			g_exit_status = WEXITSTATUS(exit_s);
		else if (WIFSIGNALED(exit_s))
			g_exit_status = 128 + WTERMSIG(exit_s);
		k++;
	}
}
