/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:48:35 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 08:48:36 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		ft_putstr_fd("getcwd ERROR!\n");
		return (1);
	}
	ft_putstr_fd(path);
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
		ft_putstr_fd(str[i]);
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
			ft_putstr_fd(minishell->envm->key);
			write(1, "=", 1);
			ft_putstr_fd(minishell->envm->value);
			write(1, "\n", 1);
		}
		minishell->envm = minishell->envm->next;
	}
}

int	builtin(t_minishell *minishell, char **command)
{
	char	*temp;

	temp = ft_tolower(command[0]);
	if (ft_strcmp(temp, "/bin/echo") == 0 || ft_strcmp(temp, "echo") == 0)
	{
		echo(command);
		return (1);
	}
	if (ft_strcmp(temp, "/usr/bin/env") == 0 || ft_strcmp(temp, "env") == 0)
	{
		env(minishell);
		return (1);
	}
	if (ft_strcmp(temp, "/bin/pwd") == 0 || ft_strcmp(temp, "pwd") == 0)
	{
		pwd();
		return (1);
	}
	return (0);
}
