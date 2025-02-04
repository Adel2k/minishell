/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:55:19 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/26 13:35:26 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	run_fork(t_minishell *minishell, int pid)
{
	pid = fork();
	if (pid == -1)
	{
		err_message("minishell: ", "Fork failed\n", "");
		g_exit_status = 1;
	}
	if (pid == 0)
	{
		pipex(minishell);
		redirs(minishell);
		if (builtin(minishell, minishell->cmd))
		{
			g_exit_status = 1;
			exit(0);
		}
		minishell->cmd = check_cmd(minishell->cmd, minishell);
		char **env_array = list_to_array(minishell->envm);
		if (execve(minishell->cmd[0], minishell->cmd,
				env_array) == -1)
		{
			err_message("minishell: ", "Executing command failed\n", "");
			free_cmd(minishell->cmd);
			exit(1);
		}
	}
}

int	run_commands2(t_minishell *minishell)
{
	if (ft_strcmp(minishell->cmd[0], "/usr/bin/cd") == 0
		|| ft_strcmp(minishell->cmd[0], "cd") == 0)
	{
		cd(minishell);
		minishell->is_builtin = 1;
		return (1);
	}
	if (ft_tolower(minishell->cmd[0], "unset") == 0)
	{
		if (minishell->cmd[1])
			unset(minishell, minishell->cmd);
		minishell->is_builtin = 1;
		return (1);
	}
	if (ft_tolower(minishell->cmd[0], "export") == 0)
	{
		if (minishell->cmd[1])
			export(minishell);
		else
			export_print(minishell->envm);
		minishell->is_builtin = 1;
		return (1);
	}
	return (0);
}

int	run_commands(t_minishell *minishell)
{
	int	pid;

	pid = 0;
	if (minishell->infile < 0 || minishell->outfile < 0)
		return (-1);
	if (minishell->pipe_count == 0)
	{
		if (run_commands2(minishell))
			return (1);
		if (ft_strcmp(minishell->cmd[0], "exit") == 0)
		{
			built_exit(minishell, 0, 0);
			minishell->is_builtin = 1;
			return (1);
		}
		exit_alt(minishell);
	}
	run_fork(minishell, pid);
	return (1);
}
