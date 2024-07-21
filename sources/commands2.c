/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:05:14 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 17:13:01 by aeminian         ###   ########.fr       */
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
	while (minishell -> cmd_dirs && minishell -> cmd_dirs[i])
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
	if (!minishell -> cmd_dirs || !minishell -> cmd_dirs[i])
	{
		free(command);
		return (0);
	}
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
		if (ft_strcmp(minishell->tokens[i].type, "word") == 0
			&& ft_strlen(minishell->tokens[i].str))
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
		err_message("minishell: ", "Malloc_err\n", "");
	while (i < minishell->tokens_count
		&& ft_strcmp(minishell->tokens[i].type, "pipe") != 0)
	{
		if (ft_strcmp(minishell->tokens[i].type, "word") == 0
			&& ft_strlen(minishell->tokens[i].str))
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
			err_message("minishell: ", minishell->cmd[0], ": command not found\n");
			// system("leaks minishell");
			exit(1);
		}
	}
	else
	{
		free(command[0]);
		command[0] = cmd;
	}
	return (command);
}
