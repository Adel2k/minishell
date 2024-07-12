/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:19 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/12 17:48:03 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_in_dirs(char *command, t_minishell *minishell)
{
	int		i;
	char	*joined_cmd;

	i = 0;
	while (minishell -> cmd_dirs[i])
	{
		joined_cmd = ft_strjoin(minishell -> cmd_dirs[i], command);
		if (access(joined_cmd, X_OK) != -1)
		{
			free(command);
			command = joined_cmd;
			break ;
		}
		free(joined_cmd);
		i++;
	}
	if (!minishell -> cmd_dirs[i])
		return (0);
	return (command);
}

int	count_cmd_args(t_minishell *minishell)
{
	int	i;
	int	count;

	i = minishell->index;
	count = 0;
	while (i < minishell->tokens_count
		&& ft_strcmp(minishell->tokens[i].type, "pipe") != 0)
	{
		if (ft_strcmp(minishell->tokens[i].type, "word") == 0)
			count++;
		i++;
	}
	return (count);
}

int	open_infile(char *file_name)
{
	int		infile_fd;

	infile_fd = open(file_name, O_RDONLY);
	if (infile_fd < 0)
		return (-1);
	return (infile_fd);
}

int	open_outfile(char *file_name, int i)
{
	int		outfile_fd;

	if (i == 0)
		outfile_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		outfile_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (outfile_fd < 0)
		return (-1);
	return (outfile_fd);
}

char	**cmd_args(t_minishell *minishell)
{
	int		i;
	int		j;
	char	**args;

	i = minishell->index;
	j = 0;
	args = malloc((count_cmd_args(minishell) + 1) * sizeof(char *));
	if (!args)
		err(minishell->tokens, minishell->tokens_count, "Malloc_err\n");
	while (i < minishell->tokens_count
		&& ft_strcmp(minishell->tokens[i].type, "pipe") != 0)
	{
		if (ft_strcmp(minishell->tokens[i].type, "in_file") == 0)
			minishell->infile = open_infile(minishell->tokens[i].str);
		if (ft_strcmp(minishell->tokens[i].type, "out_file") == 0)
			minishell->outfile = open_outfile(minishell->tokens[i].str, 0);
		if (ft_strcmp(minishell->tokens[i].type, "append_file") == 0)
			minishell->outfile = open_outfile(minishell->tokens[i].str, 1);
		if (ft_strcmp(minishell->tokens[i].type, "word") == 0)
		{
			args[j] = minishell->tokens[i].str;
			j++;
		}
		i++;
	}
	args[j] = 0;
	minishell->index = i;
	return (args);
}

char	**check_cmd(char **command, t_minishell *minishell)
{
	char	*cmd;

	cmd = check_in_dirs(ft_strdup(command[0]), minishell);
	if (!cmd)
	{
		if (access(command[0], X_OK) == -1)
			err(minishell->tokens, minishell->tokens_count, "No command\n");
	}
	else
	{
		free(command[0]);
		command[0] = cmd;
	}
	return (command);
}

void redirs(t_minishell *minishell)
{
	if (minishell->outfile > 1)
	{
		if (dup2(minishell->outfile, 1) == -1)
		{
			close(minishell->outfile);
			err(minishell->tokens, minishell->tokens_count, "dup2 error\n");
		}
		close(minishell->outfile);
	}
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, 0) == -1)
		{
			close(minishell->infile);
			err(minishell->tokens, minishell->tokens_count, "dup2 error\n");
		}
		close(minishell->infile);
	}
}

void	run_commands(t_minishell *minishell)
{
	char	**command;
	int		pid;

	command = cmd_args(minishell);
	pid = fork();
	if (pid == -1)
		err(minishell->tokens, minishell->tokens_count, "Fork failed");
	if (pid == 0)
	{
		command = check_cmd(command, minishell);
		pipex(minishell);
		redirs(minishell);
		if (execve(command[0], command, minishell -> env) == -1)
		{
			free(command);
			err(minishell->tokens, minishell->tokens_count,
				"Executing command failed\n");
		}
	}
}
