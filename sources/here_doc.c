/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:24:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/04/18 17:03:59 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2 || n <= 0)
		return (-2);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

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
		err(minishell->tokens, minishell->tokens_count, "pipe error\n");
	}
	minishell->here_doc = fd;
	minishell->if_here_doc = 1;
	while (1)
	{
		str = readline(" > ");
		//printf("%s    %s   %lu", str, limiter, ft_strlen(str));
		if (!ft_strncmp(str, limiter, ft_strlen(str)))
		{
			free(str);
			break ;
		}
		len = ft_strlen(str);
		write((*minishell -> here_doc)[1], str, len);
		free(str);
	}
	close((*minishell -> here_doc)[1]);
	return (1);
}
