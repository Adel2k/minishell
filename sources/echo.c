#include "minishell.h"

void	ft_putstr_fd(char *s)
{
	if (s)
		write (1, s, ft_strlen(s));
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
		while (str[i] == 'n' && (str[i + 1] == 'n' || str[i + 1] == ' ' || str[i + 1] == 0))
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
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		ft_putstr_fd(minishell->env[i]);
		write(1, "\n", 1);
		i++;
	}
	
}

int	builtin(t_minishell *minishell, char **command)
{
	if (ft_strcmp(command[0], "/bin/echo") == 0 || ft_strcmp(command[0], "echo") == 0)
	{
		echo(command);
		return (1);
	}
	if (ft_strcmp(command[0], "/usr/bin/env") == 0 || ft_strcmp(command[0], "env") == 0)
	{
		env(minishell);
		return (1);
	}
	return (0);
}
