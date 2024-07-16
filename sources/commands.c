/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:19 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 06:30:02 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_fork(t_minishell *minishell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		err_message("minishell: ", "Fork failed\n", "");
		exit(1);
	}
	if (pid == 0)
	{
		minishell->cmd = check_cmd(minishell->cmd, minishell);
		pipex(minishell);
		redirs(minishell);
		if (builtin(minishell, minishell->cmd))
			exit(0);
		if (execve(minishell->cmd[0], minishell->cmd, minishell -> env) == -1)
		{
			err_message("minishell: ", "Executing command failed\n", "");
			free_cmd(minishell->cmd);
			exit(1);
		}
	}
}

int	run_commands(t_minishell *minishell)
{
	minishell->cmd = cmd_args(minishell);
	if (minishell->infile < 0 || minishell->outfile < 0)
		return (-1);
	if (ft_strcmp(minishell->cmd[0], "/usr/bin/cd") == 0
		|| ft_strcmp(minishell->cmd[0], "cd") == 0)
	{
		cd(minishell);
		return (1);
	}
	if (ft_strcmp(ft_tolower(minishell->cmd[0]), "unset") == 0)
	{
		if (minishell->cmd[1])
			unset(minishell->envm, minishell->cmd[1]);
		return (1);
	}
	if (ft_strcmp(ft_tolower(minishell->cmd[0]), "export") == 0)
	{
		if (minishell->cmd[1])
			export(minishell, minishell->cmd[1]);
		else
			export_print(minishell->envm);
		return (1);
	}
	run_fork(minishell);
	return (1);
}
