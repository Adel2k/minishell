/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:19 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/15 14:17:12 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_in_dirs(char *command, t_minishell *minishell)
{
	int		i;
	char	*joined_cmd;

	if (!command || !*command)
		exit(0);
	i = 0;
	while (minishell -> cmd_dirs[i])
	{
		joined_cmd = ft_strjoin_dirs(minishell -> cmd_dirs[i], command);
		if (access(joined_cmd, X_OK | F_OK) != -1)
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
		if (ft_strcmp(minishell->tokens[i].type, "word") == 0 && ft_strlen(minishell->tokens[i].str))
			count++;
		i++;
	}
	return (count);
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
		err(minishell, "Malloc_err\n", "");
	while (i < minishell->tokens_count
		&& ft_strcmp(minishell->tokens[i].type, "pipe") != 0)
	{
		if (ft_strcmp(minishell->tokens[i].type, "word") == 0 && ft_strlen(minishell->tokens[i].str))
		{
			args[j] = ft_strdup(minishell->tokens[i].str);
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
		{
			err(minishell, command[0], ": command not found\n");
			return (0);
		}
	}
	else
	{
		free(command[0]);
		command[0] = cmd;
	}
	return (command);
}

int	run_commands(t_minishell *minishell)
{
	int		pid;

	minishell->cmd = cmd_args(minishell);
	if (minishell->infile < 0 || minishell->outfile < 0)
		return -1;
	if (ft_strcmp(minishell->cmd[0], "/usr/bin/cd") == 0 || ft_strcmp(minishell->cmd[0], "cd") == 0)
		cd(minishell);
	pid = fork();
	if (pid == -1)
	{
		err(minishell, "Fork failed\n", "");
		return (-1);
	}
	if (pid == 0)
	{
		minishell->cmd = check_cmd(minishell->cmd, minishell);
		if (!minishell->cmd)
			return (-1);
		pipex(minishell);
		redirs(minishell);
		printf("aaaa\n");
		if (builtin(minishell, minishell->cmd))
			exit(0);
		if (execve(minishell->cmd[0], minishell->cmd, minishell -> env) == -1)
		{
			err(minishell, "Executing command failed\n", "");
			return (-1);
		}
	}
	return (1);
}
