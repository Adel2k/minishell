/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:24:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/07/13 21:35:11 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *limiter, t_minishell *minishell)
{
	char	*str;
	int		len;
	int (*fd)[2];

	fd = malloc(sizeof(int[2]));
	if (pipe(*fd) == -1)
	{
		close((*fd)[0]);
		close((*fd)[1]);
		err(minishell, "pipe error\n");
	}
	minishell->here_doc = fd;
	minishell->if_here_doc = 1;
	while (1)
	{
		str = readline(" > ");
		if (!ft_strncmp(str, limiter, ft_strlen(str)))
		{
			free(str);
			break ;
		}
		str = ft_strjoin(str, "\n"); // need to free
		len = ft_strlen(str);
		write((*minishell -> here_doc)[1], str, len);
		free(str);
	}
	close((*minishell -> here_doc)[1]);
	return (1);
}
