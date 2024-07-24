/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:48:35 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 15:38:38 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

int	pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		ft_putstr_fd("getcwd ERROR!\n", 2);
		return (1);
	}
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	return (0);
}

int	check_newline(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == 0 || str[i] != '-')
		return (0);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] == 'n' && (str[i + 1] == 'n'
				|| str[i + 1] == ' ' || str[i + 1] == 0))
		{
			if (str[i + 1] == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

void	echo(char **str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (check_newline(str[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (i + 1 != matrix_len(str))
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	env(t_minishell *minishell)
{
	if (minishell->cmd[1])
	{
		err_message("minishell: ", minishell->cmd[1],
			": No such file or directory");
		return ;
	}
	while (minishell->envm)
	{
		if (minishell->envm->value)
		{
			ft_putstr_fd(minishell->envm->key, 2);
			write(1, "=", 1);
			ft_putstr_fd(minishell->envm->value, 1);
			write(1, "\n", 1);
		}
		minishell->envm = minishell->envm->next;
	}
}

int	builtin(t_minishell *minishell, char **command)
{
	if (ft_tolower(command[0], "/bin/echo") == 0 || ft_tolower(command[0], "echo") == 0)
	{
		echo(command);
		return (1);
	}
	if (ft_tolower(command[0], "/usr/bin/env") == 0 || ft_tolower(command[0], "env") == 0)
	{
		env(minishell);
		return (1);
	}
	if (ft_tolower(command[0], "/bin/pwd") == 0 || ft_tolower(command[0], "pwd") == 0)
	{
		pwd();
		return (1);
	}
	if (ft_strcmp(minishell->cmd[0], "/usr/bin/cd") == 0
		|| ft_strcmp(minishell->cmd[0], "cd") == 0)
	{
		cd(minishell);
		return (1);
	}
	if (ft_tolower(minishell->cmd[0], "unset") == 0)
	{
		if (minishell->cmd[1])
			unset(minishell, minishell->cmd);
		return (1);
	}
	if (ft_tolower(minishell->cmd[0], "export") == 0)
	{
		if (minishell->cmd[1])
			export(minishell);
		else
			export_print(minishell->envm);
		return (1);
	}
	if (ft_strcmp(minishell->cmd[0], "exit") == 0)
	{
		built_exit(minishell, 1, 0);
		return (1);
	}
	return (0);
}
