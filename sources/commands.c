/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:19 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/11 13:55:24 by aeminian         ###   ########.fr       */
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

char	**check_cmd(t_minishell *minishell)
{
	char	**command;
	char	*cmd;

	command = cmd_args(minishell);
	cmd = check_in_dirs(ft_strdup(command[0]), minishell);
	if (!cmd)
	{
		if (access(command[0], X_OK) == -1)
			err(minishell->tokens, minishell->tokens_count, "No command");
	}
	else
	{
		free(command[0]);
		command[0] = cmd;
	}
	return (command);
}

void	run_commands(t_minishell *minishell)
{
	char	**command;
	int		pid;

	command = check_cmd(minishell);
	pid = fork();
	if (pid == -1)
		err(minishell->tokens, minishell->tokens_count, "Fork failed");
	if (pid == 0)
	{
		pipex(minishell);
		if (execve(command[0], command, minishell -> env) == -1)
		{
			free(command);
			err(minishell->tokens, minishell->tokens_count,
				"Executing command failed\n");
		}
	}
	// else
		// waitpid(pid, NULL, 0); // AVELACNEL STATUSI STUGUM(2RD ARGUMENT)
}
