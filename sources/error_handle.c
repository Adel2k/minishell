/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:56:05 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/11 13:56:06 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	k = 0;
	while (k < minishell->pipe_count + 1)
	{
		waitpid(-1, NULL, 0); // AVELACNEL STATUSI STUGUM(2RD ARGUMENT)
		k++;
	}
}
