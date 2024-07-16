/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:50:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 08:50:55 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirs(t_minishell *minishell)
{
	int	i;

	i = minishell->index - 1;
	while (++i < minishell->tokens_count
		&& ft_strcmp(minishell->tokens[i].type, "pipe") != 0)
	{
		if (ft_strcmp(minishell->tokens[i].type, "in_file") == 0)
		{
			minishell->infile_name = minishell->tokens[i].str;
			minishell->infile = open_infile(minishell->tokens[i].str);
		}
		if (ft_strcmp(minishell->tokens[i].type, "out_file") == 0)
		{
			minishell->outfile_name = minishell->tokens[i].str;
			minishell->outfile = open_outfile(minishell->tokens[i].str, 0);
		}
		if (ft_strcmp(minishell->tokens[i].type, "append_file") == 0)
		{
			minishell->outfile_name = minishell->tokens[i].str;
			minishell->outfile = open_outfile(minishell->tokens[i].str, 1);
		}
		if (ft_strcmp(minishell->tokens[i].type, "limiter") == 0)
			minishell->if_here_doc
				= here_doc(minishell->tokens[i].str, minishell);
	}
}

t_env	*init_env(t_minishell *minishell)
{
	t_env	*res;
	int		i;

	res = NULL;
	i = -1;
	while (minishell->env[++i] != 0)
		add_nodes(ft_strdup(minishell->env[i]), &res);
	return (res);
}

char	**init_dirs(t_minishell *minishell)
{
	int		i;
	char	**dirs;

	i = 0;
	while (minishell -> env[i])
	{
		if (ft_strstr_alt(minishell -> env[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(minishell -> env[i] + 5, ':');
	if (!dirs)
	{
		err_message("minishell: ", "split_err\n", "");
		return (0);
	}
	return (dirs);
}

int	init_cmd_line(t_minishell *minishell, char *input)
{
	char	**strs;

	minishell->tokens_count = ft_words_count_tokens(input, ' ');
	if (minishell->tokens_count < 0)
	{
		printf("hehehe\n");
		free(input);
		return (-1);
	}
	strs = ft_split_tokens(input);
	minishell->tokens = tokenisation(strs, minishell->tokens_count);
	free(strs);
	free(input);
	minishell->pipe_count = pipe_count(minishell);
	minishell->pipe_index = 0;
	minishell->index = 0;
	if (minishell->pipe_count && init_fd(minishell) < 0)
		return (-1);
	if (check_for_invalid_input(minishell->tokens, minishell->tokens_count) < 0)
		return (-1);
	dollar_sign(minishell->tokens, minishell->tokens_count, minishell);
	remove_quotes(minishell);
	return (1);
}

int	init_fd(t_minishell *minishell)
{
	int	(*fd)[2];
	int	i;

	i = 0;
	fd = malloc(sizeof(int [2]) * (minishell->pipe_count));
	malloc_check(fd);
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
			err_message("minishell: ", "pipe error\n", "");
			return (-1);
		}
		i++;
	}
	minishell->fd = fd;
	return (1);
}
