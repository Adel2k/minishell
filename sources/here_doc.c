/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:24:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/07/15 23:09:08 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_here_doc(t_minishell *minishell, char *limiter)
{
	int		len;
	char	*str;

	while (1)
	{
		str = readline(" > ");
		if (!str)
			break ;
		if (!ft_strncmp(str, limiter, ft_strlen(str)))
		{
			free(str);
			break ;
		}
		str = ft_strjoin(str, "\n");
		len = ft_strlen(str);
		write((*minishell -> here_doc)[1], str, len);
		free(str);
	}
}

int	here_doc(char *limiter, t_minishell *minishell)
{
	int	(*fd)[2];

	fd = malloc(sizeof(int [2]));
	if (pipe(*fd) == -1)
	{
		close((*fd)[0]);
		close((*fd)[1]);
		err_message("minishell: ", "pipe error\n", "");
		return (-1);
	}
	minishell->here_doc = fd;
	minishell->if_here_doc = 1;
	run_here_doc(minishell, limiter);
	close((*minishell -> here_doc)[1]);
	return (1);
}
