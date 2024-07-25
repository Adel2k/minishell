/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/25 18:54:22 by hrigrigo         ###   ########.fr       */
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

t_env	*init_env(char **env)
{
	t_env	*res;
	t_env *tmp;
	int		i;

	res = NULL;
	i = -1;
	while (env[++i] != 0)
		add_nodes(env[i], &res);
	tmp = res;
	while (tmp && ft_strcmp(tmp->key, "SHLVL"))
		tmp = tmp->next;
	if (!tmp)
	{
		add_nodes("SHLVL=0", &res);
	}
	return (res);
}

char	**init_dirs(t_minishell *minishell)
{
	int		i;
	char	**dirs;
	t_env	*tmp;

	tmp = minishell->envm;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	dirs = ft_split(tmp->value, ':');
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
		return (-1);
	strs = ft_split_tokens(input);
	minishell->tokens = tokenisation(strs, minishell->tokens_count);
	free(strs);
	minishell->pipe_count = pipe_count(minishell);
	minishell->pipe_index = 0;
	minishell->index = 0;
	if (minishell->pipe_count && init_fd(minishell) < 0)
		return (-1);
	if (if_invalid_input(minishell->tokens, minishell->tokens_count, -1) < 0)
		return (-1);
	dollar_sign(minishell->tokens, minishell->tokens_count, minishell);
	remove_quotes(minishell);
	free(input);
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
