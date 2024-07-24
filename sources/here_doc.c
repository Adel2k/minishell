/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:24:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/07/23 19:41:56 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*s3;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[i - s1_size])
	{
		s3[i] = s2[i - s1_size];
		i++;
	}
	free(s1);
	s3[i] = '\0';
	return (s3);
}

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
		str = ft_strjoin_heredoc(str, "\n");
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
